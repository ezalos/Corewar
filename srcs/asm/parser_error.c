/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:24:38 by gtaja             #+#    #+#             */
/*   Updated: 2019/11/03 20:57:17 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*get_error_message_next(int code)
{
	if (code == PARSER_WRONG_ARGS_NUMBER)
		return ("Incorrect number of arguments");
	else if (code == PARSER_BAD_REGISTER)
		return ("Incorrect Register");
	else if (code == PARSER_UNKNOW_LABEL)
		return ("Unknown label");
	else if (code == PARSER_LABEL_REDEFINE)
		return ("Label already defined");
	else if (code == PARSER_ENDS_WITHOUT_NL)
		return ("unexpected end of input "
		"(Perhaps you forgot to end with a newline ?)");
	else if (code == PARSER_WRONG_FILE)
		return ("Corrupted file");
	else if (code == PARSER_BAD_NUMBER)
		return ("Bad number");
	else if (code == PARSER_EMPTY_CODE)
		return ("There is no code");
	return (NULL);
}

static char	*get_error_message(int code)
{
	if (code == PARSER_CANT_OPEN_SOURCE)
		return ("Can't open source file");
	else if (code == PARSER_CANT_CREATE_BINARY)
		return ("Can't create binary file.");
	else if (code == PARSER_BAD_CMD)
		return ("Unknown command");
	else if (code == PARSER_MULTIPLE_NAME)
		return ("Multiple .name");
	else if (code == PARSER_MULTIPLE_COMMENT)
		return ("Multiple .comment");
	else if (code == PARSER_BAD_STRING)
		return ("Incorrect string");
	else if (code == PARSER_TOO_LONG_NAME)
		return ("Champion name too long");
	else if (code == PARSER_TOO_LONG_COMMENT)
		return ("Champion comment too long");
	else if (code == PARSER_BAD_LABEL)
		return ("Incorrect label");
	else if (code == PARSER_BAD_INSTRUCTION)
		return ("Incorrect instruction");
	else if (code == PARSER_BAD_ARG_TYPE)
		return ("Incorrect argument type");
	else if (code == PARSER_BAD_ARG_VALUE)
		return ("Incorrect argument value");
	return (get_error_message_next(code));
}

void		parser_log_error(t_parser *parser, int code)
{
	char	*msg;

	msg = get_error_message(code);
	if (msg != NULL)
	{
		ft_putstr_fd("Error at line ", 2);
		ft_putnbr_fd(parser->line, 2);
		ft_putstr_fd(" - ", 2);
		ft_putendl_fd(msg, 2);
	}
}
