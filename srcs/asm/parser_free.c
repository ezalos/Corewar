/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:10:28 by gtaja             #+#    #+#             */
/*   Updated: 2019/11/01 15:18:46 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	free_labels(t_list *labels)
{
	t_list	*it;
	t_list	*tmp;
	t_label	*content;

	it = labels;
	while (it != NULL)
	{
		tmp = it->next;
		content = (t_label*)(it->content);
		ft_memdel((void**)&content->name);
		ft_memdel((void**)&content);
		ft_memdel((void**)&it);
		it = tmp;
	}
}

static void	free_waiting_labels(t_list *labels)
{
	t_list			*it;
	t_list			*tmp;
	t_waiting_label	*content;

	it = labels;
	while (it != NULL)
	{
		tmp = it->next;
		content = (t_waiting_label*)(it->content);
		ft_memdel((void**)&content->name);
		ft_memdel((void**)&content);
		ft_memdel((void**)&it);
		it = tmp;
	}
}

void		parser_free(t_parser *parser)
{
	free_labels(parser->labels);
	free_waiting_labels(parser->waitings_labels);
	binary_free(&(parser->binary));
}
