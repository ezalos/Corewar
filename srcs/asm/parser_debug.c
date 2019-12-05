/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 15:30:12 by gtaja             #+#    #+#             */
/*   Updated: 2019/10/01 16:00:23 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parser_debug_header(t_parser *parser)
{
	ft_printf("MAGIC   = %d\n", parser->header.magic);
	ft_printf("NAME    = '%s'\n", parser->header.prog_name);
	ft_printf("COMMENT = '%s'\n", parser->header.comment);
	ft_printf("SIZE    = %d\n", parser->header.prog_size);
}
