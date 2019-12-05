/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 14:00:33 by gtaja             #+#    #+#             */
/*   Updated: 2019/11/03 17:50:29 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Verifie que la ligne n'est pas un commentaire ou une ligne vide
** Augmente le compteur et trim la chaine (si non vide)
*/

static int	check_line(t_parser *parser, char **line)
{
	*line = ft_strtrim_free(*line);
	parser->line += 1;
	if (line[0][0] == COMMENT_CHAR || line[0][0] == '\0')
	{
		ft_memdel((void**)&*line);
		return (FALSE);
	}
	return (TRUE);
}

/*
** Verifie que la ligne termine par une newline
*/

static int	check_newline(char *line)
{
	int	i;

	if (line[ft_strlen(line) - 1] == '\n')
		return (TRUE);
	else
	{
		i = 0;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		return (line[i] == '\0');
	}
}

/*
** Encule la norminette avec classe
*/

static int	fuck_you_norminette(int fct_res, char *line)
{
	ft_memdel((void**)&line);
	return (fct_res);
}

/*
** Fini la fonction main
*/

static int	finish_parsing(t_parser *parser)
{
	if (parser->state != INSTRCUTIONS)
		return (PARSER_WRONG_FILE);
	return (parser_export(parser));
}

/*
** Boucle principal qui lit ligne par ligne et redirige selon l'état
*/

int			parser_main(t_parser *parser)
{
	char	*line;
	int		fct_res;

	while (gnl_check_zero(parser->fd_source, &line, TRUE) > 0)
	{
		if (!check_newline(line))
			return (fuck_you_norminette(PARSER_ENDS_WITHOUT_NL, line));
		if (!check_line(parser, &line))
			continue ;
		if (parser->state == HEADER)
		{
			if ((fct_res = parser_header(parser, line)) != PARSER_SUCCESS)
				return (fuck_you_norminette(fct_res, line));
		}
		else if (parser->state == INSTRCUTIONS)
		{
			if ((fct_res = parser_instruction(parser, line)) != PARSER_SUCCESS)
				return (fuck_you_norminette(fct_res, line));
		}
		ft_memdel((void**)&line);
	}
	if ((fct_res = parser_manage_labels(parser)) != PARSER_SUCCESS)
		return (fct_res);
	return (finish_parsing(parser));
}
