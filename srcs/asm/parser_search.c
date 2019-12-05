/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_search.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 13:42:52 by gtaja             #+#    #+#             */
/*   Updated: 2019/11/03 22:20:54 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Skip les espaces, taabulation et newline
*/

void		skip_whitespace(char **str)
{
	while (**str == ' ' || **str == '\t' || **str == '\n')
		*str = *str + 1;
	if (**str == COMMENT_CHAR)
		*str = *str + ft_strlen(*str);
}

/*
** Check la validité de la fin de la chaine
** (apres le ", on verifie qu'on est sur une chaine vide
**  ou pleine de whitespace)
** Free str a la fin
** En cas d'echec, on free aussi result
*/

static int	is_valid_end(char *str, int j, int need_free, char **result)
{
	int	i;

	i = j + 1;
	while (str[i] != '\0')
	{
		if (str[i] == COMMENT_CHAR)
			break ;
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
		{
			if (need_free)
				ft_memdel((void**)&str);
			ft_memdel((void**)result);
			return (0);
		}
		i++;
	}
	if (need_free)
		ft_memdel((void**)&str);
	return (1);
}

/*
** Free str si besoin
** Appel GNL (+ increment parser->line)
** Realloc result
*/

static int	call_gnl_for_me_bro(t_parser *parser, int *need_free,
	char **str, char **result)
{
	if (*need_free)
		ft_memdel((void**)&*str);
	if (gnl(parser->fd_source, str) <= 0)
	{
		ft_memdel((void**)result);
		return (PARSER_BAD_STRING);
	}
	*need_free = 1;
	parser->line += 1;
	*result = ft_strrealloc(*result, ft_strlen(*result) + ft_strlen(*str) + 1);
	return (PARSER_SUCCESS);
}

/*
** Debut de la fonction parser_search_string
**	if (**str != ' ' && **str != '\t')
**		return (PARSER_BAD_CMD);
*/

static int	init_search_string(char **str, char **result)
{
	int	len;

	skip_whitespace(str);
	len = ft_strlen(*str);
	if (len < 1 || str[0][0] != '"')
		return (PARSER_BAD_STRING);
	*result = ft_strnew(len);
	return (PARSER_SUCCESS);
}

/*
** Recupere la string dans la chaine suivante
** - La chaine doit commencer et finir par "
** - Les " doivent etre echapé par \
*/

int			parser_search_string(t_parser *parser, char *str, char **result)
{
	int	i;
	int	j;
	int	fct_res;
	int	need_free;

	i = 0;
	j = 1;
	need_free = 0;
	if ((fct_res = init_search_string(&str, result)) < 0)
		return (fct_res);
	while (str[j] != '"')
	{
		if (str[j] == '\0')
		{
			if ((fct_res = call_gnl_for_me_bro(parser,
				&need_free, &str, result)) < 0)
				return (fct_res);
			j = 0;
		}
		if (str[j] != '"')
			(*result)[i++] = str[j++];
	}
	(*result)[i] = '\0';
	return (is_valid_end(str, j, need_free, result) ?
		PARSER_SUCCESS : PARSER_BAD_STRING);
}
