/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_label.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 13:42:24 by gtaja             #+#    #+#             */
/*   Updated: 2019/11/01 15:20:25 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Retourne le label de reference demmandé par un waiting_label
** Set la ligne du parser à la ligne de l'erreur si besoin
*/

static t_label	*get_label(t_parser *parser, t_waiting_label *wait)
{
	t_list	*it;
	t_label	*lbl;

	it = parser->labels;
	while (it != NULL)
	{
		lbl = (t_label*)(it->content);
		if (ft_strequ(lbl->name, wait->name))
			return (lbl);
		it = it->next;
	}
	parser->line = wait->line;
	return (NULL);
}

/*
** Defini le binaire de tout les waiting_label
*/

int				parser_manage_labels(t_parser *parser)
{
	t_list			*it;
	t_label			*lbl;
	t_waiting_label	*wait;
	uint32_t		value;
	uint8_t			*reverse;

	it = parser->waitings_labels;
	while (it != NULL)
	{
		wait = (t_waiting_label*)(it->content);
		if ((lbl = get_label(parser, wait)) == NULL)
			return (PARSER_UNKNOW_LABEL);
		binary_seek(&(parser->binary), wait->cursor, SEEK_SET);
		value = lbl->address - wait->address;
		reverse = switch_endian((uint8_t*)(&value), wait->size);
		binary_write(&(parser->binary), reverse, wait->size);
		ft_memdel((void**)&reverse);
		it = it->next;
	}
	return (PARSER_SUCCESS);
}
