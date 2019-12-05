/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 14:22:48 by ldevelle          #+#    #+#             */
/*   Updated: 2019/11/02 12:35:40 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void		visu_champ(t_vm *vm, t_champion champ, int row, int col)
{
	int		i;

	i = 0;
	wattron(vm->visu.w_panel, COLOR_PAIR(champ.number));
	wmove(vm->visu.w_panel, i++ + row, col + 5);
	wprintw(vm->visu.w_panel, "N%d is ", champ.number);
	if (champ.alive)
		wprintw(vm->visu.w_panel, "Alive");
	else
	{
		wprintw(vm->visu.w_panel, "Dead ");
		wattroff(vm->visu.w_panel, COLOR_PAIR(champ.number));
		wattron(vm->visu.w_panel, COLOR_PAIR(NP_COLOR));
	}
	wmove(vm->visu.w_panel, i++ + row, col);
	wmove(vm->visu.w_panel, i++ + row, col);
	wprintw(vm->visu.w_panel, "%-30s", champ.name);
	wmove(vm->visu.w_panel, i++ + row, col);
	wprintw(vm->visu.w_panel, "%-30s", champ.comment);
	wmove(vm->visu.w_panel, i++ + row, col);
	wmove(vm->visu.w_panel, i++ + row, col);
	wprintw(vm->visu.w_panel, "live:\t%d", champ.lives_since_check);
	wmove(vm->visu.w_panel, i++ + row, col);
	wprintw(vm->visu.w_panel, "last live:\t%d", champ.last_live_cycle);
	wattroff(vm->visu.w_panel, COLOR_PAIR(champ.number));
}

void		visu_opt(t_vm *vm, int row, int col)
{
	int		i;

	i = row;
	wattron(vm->visu.w_panel, COLOR_PAIR(NP_COLOR));
	wmove(vm->visu.w_panel, i++ + UP_SPACE, 0 + LEFT_SPACE + col);
	wprintw(vm->visu.w_panel, "dump_cycles: %d", vm->options.dump_cycles);
	wmove(vm->visu.w_panel, i++ + UP_SPACE, 0 + LEFT_SPACE + col);
	wprintw(vm->visu.w_panel, "MAX_CHECKS: %3d/%-3d", vm->max_checks,
		MAX_CHECKS);
	wmove(vm->visu.w_panel, i++ + UP_SPACE, 0 + LEFT_SPACE + col);
	wprintw(vm->visu.w_panel, "NBR_LIVE: %d", NBR_LIVE);
	wmove(vm->visu.w_panel, i++ + UP_SPACE, 0 + LEFT_SPACE + col);
	wprintw(vm->visu.w_panel, "nb_champ: %d", vm->options.nb_champ);
	wattroff(vm->visu.w_panel, COLOR_PAIR(NP_COLOR));
}

void		visu_update_next(t_vm *vm)
{
	int		champ_space;
	int		champ_space_r;

	wattron(vm->visu.w_panel, COLOR_PAIR(GD_COLOR));
	wprintw(vm->visu.w_panel, "Total processus: %7d", vm->tt_pc);
	wattroff(vm->visu.w_panel, COLOR_PAIR(GD_COLOR));
	wattroff(vm->visu.w_panel, COLOR_PAIR(WH_COLOR));
	visu_opt(vm, 2, 60);
	visu_speed(vm, 8, 15);
	champ_space = 10;
	champ_space_r = 40;
	visu_champ(vm, vm->champions[vm->options.number_champ[0] - 1],
		H_PANEL - (champ_space * 2), 5);
	if (vm->options.nb_champ > 1)
		visu_champ(vm, vm->champions[vm->options.number_champ[1] - 1],
			H_PANEL - (champ_space * 2), 5 + W_PANEL - champ_space_r);
	if (vm->options.nb_champ > 2)
		visu_champ(vm, vm->champions[vm->options.number_champ[2] - 1],
			H_PANEL - (champ_space * 1), 5);
	if (vm->options.nb_champ > 3)
		visu_champ(vm, vm->champions[vm->options.number_champ[3] - 1],
			H_PANEL - (champ_space * 1), 5 + W_PANEL - champ_space_r);
}

void		visu_update_panel(t_vm *vm)
{
	int		i;
	int		col;

	if ((i = 1) && vm->visu.visu)
	{
		visu_border(vm, V_PANEL);
		col = 2;
		wattron(vm->visu.w_panel, COLOR_PAIR(GD_COLOR));
		wattron(vm->visu.w_panel, A_UNDERLINE | A_BOLD);
		wmove(vm->visu.w_panel, i++ + UP_SPACE, 40 - ((8 + 4) / 2));
		wprintw(vm->visu.w_panel, "CYCLES: %d", vm->cycle);
		wattroff(vm->visu.w_panel, COLOR_PAIR(GD_COLOR));
		wattroff(vm->visu.w_panel, A_UNDERLINE | A_BOLD);
		wattron(vm->visu.w_panel, COLOR_PAIR(WH_COLOR));
		wmove(vm->visu.w_panel, i++ + UP_SPACE, 0 + LEFT_SPACE + col);
		wprintw(vm->visu.w_panel, "cycle to die: %5d/%-5d  ",
			vm->cycle_to_die - vm->current_cycle, vm->cycle_to_die);
		wmove(vm->visu.w_panel, i++ + UP_SPACE, 0 + LEFT_SPACE + col);
		wprintw(vm->visu.w_panel, "cycle delta: %5d", CYCLE_DELTA);
		wmove(vm->visu.w_panel, i++ + UP_SPACE, 0 + LEFT_SPACE + col);
		wprintw(vm->visu.w_panel, "Total lives since check: %5d",
			vm->total_live_since_check);
		wmove(vm->visu.w_panel, i++ + UP_SPACE, 0 + LEFT_SPACE + col);
		visu_update_next(vm);
	}
}
