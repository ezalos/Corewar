/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 13:40:53 by gtaja             #+#    #+#             */
/*   Updated: 2019/11/03 22:21:39 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Retourne le type du parametre commançant à *line
*/

t_arg_type	get_arg_type_asm(char **line)
{
	t_arg_type	type;

	if (line[0][0] == 'r' || line[0][0] == DIRECT_CHAR)
	{
		type = line[0][0] == 'r' ? T_REG : T_DIR;
		*line = *line + 1;
	}
	else
		type = T_IND;
	return (type);
}

/*
** Retourne la taille du parametre en octet
*/

size_t		get_arg_length(t_arg_type type, t_op *op)
{
	if (type == T_REG)
		return (1);
	else if (type == T_IND)
		return (2);
	else if (type == T_DIR)
		return (op->is_direct_two_bytes ? 2 : 4);
	return (0);
}
