/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 14:51:06 by gtaja             #+#    #+#             */
/*   Updated: 2019/10/22 16:10:27 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lib.h"

/*
** Ecrit le binaire dans le fd_bin
*/

int				parser_export(t_parser *parser)
{
	int	fd;

	parser->header.prog_size = binary_size(&(parser->binary));
	if (parser->header.prog_size <= 0)
		return (PARSER_EMPTY_CODE);
	if ((parser->fd_bin =
		open(parser->out_file, O_WRONLY | O_TRUNC | O_CREAT, 0666)) < 0)
		return (PARSER_CANT_CREATE_BINARY);
	fd = parser->fd_bin;
	write_switch_endian(fd, parser->header.magic);
	write(fd, parser->header.prog_name, round_next_four(PROG_NAME_LENGTH + 1));
	write_switch_endian(fd, parser->header.prog_size);
	write(fd, parser->header.comment, round_next_four(COMMENT_LENGTH + 1));
	binary_export(&(parser->binary), fd);
	return (PARSER_SUCCESS);
}
