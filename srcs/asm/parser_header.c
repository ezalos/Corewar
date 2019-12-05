/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_header.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 13:11:46 by gtaja             #+#    #+#             */
/*   Updated: 2019/11/01 15:20:34 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	apply_cmd(t_parser *parser, char *line, char *cmd, char **target)
{
	int		fct_res;
	char	*str;

	if (ft_strstartwith(line, cmd))
	{
		if ((fct_res = parser_search_string(parser,
			line + ft_strlen(cmd), &str)) != PARSER_SUCCESS)
		{
			return (fct_res);
		}
		*target = str;
		return (PARSER_SUCCESS);
	}
	return (PARSER_IGNORE);
}

static int	header_check_state(t_parser *parser, int success)
{
	if (success != 1)
		return (PARSER_BAD_CMD);
	else if (parser->name_count > 1)
		return (PARSER_MULTIPLE_NAME);
	else if (parser->comment_count > 1)
		return (PARSER_MULTIPLE_COMMENT);
	else if (parser->comment_count == 1 && parser->name_count == 1)
		parser->state = INSTRCUTIONS;
	return (PARSER_SUCCESS);
}

static int	get_name(t_parser *parser, char *line, int *success)
{
	int		result;
	char	*str;

	result = apply_cmd(parser, line, NAME_CMD_STRING, &str);
	if (result == PARSER_SUCCESS)
	{
		if (ft_strlen(str) > PROG_NAME_LENGTH)
		{
			ft_memdel((void**)&str);
			return (PARSER_TOO_LONG_NAME);
		}
		parser->name_count += 1;
		ft_strcpy(parser->header.prog_name, str);
		*success = *success + 1;
		ft_memdel((void**)&str);
	}
	return (result);
}

static int	get_comment(t_parser *parser, char *line, int *success)
{
	int		result;
	char	*str;

	result = apply_cmd(parser, line, COMMENT_CMD_STRING, &str);
	if (result == PARSER_SUCCESS)
	{
		if (ft_strlen(str) > COMMENT_LENGTH)
		{
			ft_memdel((void**)&str);
			return (PARSER_TOO_LONG_COMMENT);
		}
		parser->comment_count += 1;
		ft_strcpy(parser->header.comment, str);
		*success = *success + 1;
		ft_memdel((void**)&str);
	}
	return (result);
}

/*
** Parse une ligne du header et selon le cas enregistre le nom ou le comment
** Change l'état du parser à INSTRUCTIONS quand le header est complet
*/

int			parser_header(t_parser *parser, char *line)
{
	int		fct_res;
	int		success;

	success = 0;
	fct_res = get_name(parser, line, &success);
	if (fct_res != PARSER_SUCCESS && fct_res != PARSER_IGNORE)
		return (fct_res);
	fct_res = get_comment(parser, line, &success);
	if (fct_res != PARSER_SUCCESS && fct_res != PARSER_IGNORE)
		return (fct_res);
	return (header_check_state(parser, success));
}
