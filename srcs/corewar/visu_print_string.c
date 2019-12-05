/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_print_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 16:30:32 by gtaja             #+#    #+#             */
/*   Updated: 2019/11/01 16:30:56 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"
#include "doigts_dans_le_cul_de_la_norminette.h"

static t_visu_str_wrap	init_wrap(char *str, int col, int row)
{
	t_visu_str_wrap	w;

	w.str = str;
	w.col = col;
	w.row = row;
	ft_memmove(w.path, "./ressources/alphabet/ \0", 24);
	w.len = ft_strlen(str);
	w.i = -1;
	w.c_supp = 0;
	w.r_supp = 0;
	return (w);
}

static void				visu_print_string_start(t_visu_str_wrap *w)
{
	w->str[w->i] = ft_toupper(w->str[w->i]);
	if (ft_isalnum(w->str[w->i]) || w->str[w->i] == '!' ||
		w->str[w->i] == '?' || w->str[w->i] == '$')
	{
		w->path[22] = w->str[w->i];
		w->width_letter = visu_place_ascii(NULL, w->path,
			w->row + w->r_supp, w->col + w->c_supp);
	}
	else if (w->str[w->i] == ' ')
		w->width_letter = 8020;
	else
	{
		w->path[22] = '$';
		w->width_letter = visu_place_ascii(NULL, w->path,
			w->row + w->r_supp, w->col + w->c_supp);
	}
}

static void				visu_print_string_end(t_vm *vm, t_visu_str_wrap *w)
{
	if (w->c_supp + w->col > 330)
	{
		w->r_supp += (w->width_letter / 1000) + 1;
		w->c_supp = 0;
	}
	else
		w->c_supp += (w->width_letter % 1000) + 2;
	visu_refresh(vm, V_V);
	control_speed(vm);
}

int						visu_print_string(t_vm *vm, char *str, int col, int row)
{
	t_visu_str_wrap	w;

	w = init_wrap(str, col, row);
	while (++w.i < w.len)
	{
		visu_print_string_start(&w);
		visu_print_string_end(vm, &w);
	}
	w.r_supp += (w.width_letter / 1000) + 1;
	return ((w.r_supp * 1000) + w.c_supp);
}
