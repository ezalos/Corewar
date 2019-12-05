/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_intro.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 15:13:34 by ldevelle          #+#    #+#             */
/*   Updated: 2019/11/02 16:08:37 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"
#include "doigts_dans_le_cul_de_la_norminette.h"

static void	visu_print_intro_end(t_vm *vm, t_visu_intro_wrap *w)
{
	while (++w->i < vm->options.nb_champ)
	{
		attron(COLOR_PAIR(
			vm->champions[vm->options.number_champ[w->i] - 1].number));
		w->number = ft_nb_to_a(
			vm->champions[vm->options.number_champ[w->i] - 1].number, 10);
		visu_print_string(vm, w->number, w->col, w->row);
		ft_memdel((void**)&(w->number));
		w->tmp = visu_print_string(vm,
			vm->champions[vm->options.number_champ[w->i] - 1].name,
			w->col + 40, w->row);
		w->row += w->tmp / 1000;
		attroff(COLOR_PAIR(
			vm->champions[vm->options.number_champ[w->i] - 1].number));
	}
	w->row += 5;
	attron(COLOR_PAIR(GD_COLOR));
	w->number = ft_strdup("May the best win!");
	visu_print_string(vm, w->number, w->col + 20, w->row);
	ft_memdel((void**)&(w->number));
	attroff(COLOR_PAIR(GD_COLOR));
	sleep(1);
}

void		visu_print_intro(t_vm *vm)
{
	t_visu_intro_wrap	w;

	w.i = -1;
	w.col = 5;
	w.row = 0;
	attron(COLOR_PAIR(WH_COLOR));
	w.number = ft_strdup("Welcome to COREWAR");
	w.tmp = visu_print_string(vm, w.number, w.col, w.row);
	ft_memdel((void**)&(w.number));
	w.row += w.tmp / 1000;
	attroff(COLOR_PAIR(WH_COLOR));
	attron(COLOR_PAIR(RD_COLOR));
	w.number = ft_strdup("TONIGHTS FIGHTERS");
	w.tmp = visu_print_string(vm, w.number, w.col + 20, w.row);
	ft_memdel((void**)&(w.number));
	attroff(COLOR_PAIR(RD_COLOR));
	w.row += w.tmp / 1000;
	w.row += 5;
	visu_print_intro_end(vm, &w);
	vm->visu.pause = 1;
	vm->visu.speed = SPEED_INIT;
}

static void	visu_print_outro_end(t_vm *vm, t_visu_intro_wrap *w)
{
	w->row += w->tmp / 1000;
	w->row += 5;
	attron(COLOR_PAIR(vm->last_alive_champ->number));
	w->number = ft_nb_to_a(vm->last_alive_champ->number, 10);
	w->tmp = visu_print_string(vm, w->number, w->col, w->row);
	ft_memdel((void**)&(w->number));
	w->col += w->tmp % 1000;
	w->col += 10;
	w->tmp = visu_print_string(vm,
		vm->last_alive_champ->name, w->col + 40, w->row);
	w->row += w->tmp / 1000;
	attroff(COLOR_PAIR(
		vm->champions[vm->options.number_champ[w->i] - 1].number));
	attron(COLOR_PAIR(RD_COLOR));
	visu_place_ascii(NULL, "./ressources/dragon.ascii",
		w->row + 10, w->col + 30);
	attroff(COLOR_PAIR(RD_COLOR));
}

void		visu_outro_follow(t_vm *vm, t_visu_intro_wrap w)
{
	if (vm->last_alive_champ)
	{
		w.number = ft_nb_to_a(vm->cycle, 10);
		w.tmp = visu_print_string(vm, w.number, w.col, w.row);
		ft_memdel((void**)&(w.number));
		visu_print_outro_end(vm, &w);
	}
	else
	{
		w.number = ft_strdup("NOBODY");
		w.tmp = visu_print_string(vm, w.number, w.col, w.row);
		ft_memdel((void**)&(w.number));
	}
	sleep(5);
}

void		visu_print_outro(t_vm *vm)
{
	t_visu_intro_wrap	w;

	w.i = -1;
	w.col = 0;
	w.row = 0;
	vm->visu.speed = SPEED_INIT;
	vm->visu.pause = 0;
	visu_erase(vm, V_ALL);
	attron(COLOR_PAIR(GD_COLOR));
	w.col += visu_place_ascii(NULL, "./ressources/michael.ascii",
		w.row, w.col) % 1000;
	w.col += 5;
	attroff(COLOR_PAIR(GD_COLOR));
	visu_refresh(vm, V_V);
	attron(COLOR_PAIR(WH_COLOR));
	w.number = ft_strdup("THE WINNER IS");
	w.tmp = visu_print_string(vm, w.number, w.col, w.row);
	ft_memdel((void**)&(w.number));
	w.row += w.tmp / 1000;
	attroff(COLOR_PAIR(WH_COLOR));
	visu_outro_follow(vm, w);
	endwin();
}
