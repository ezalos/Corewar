/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_speed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 16:02:53 by gtaja             #+#    #+#             */
/*   Updated: 2019/11/02 21:31:51 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

static void	visu_speed_three(t_vm *vm, int col, int i)
{
	wmove(vm->visu.w_panel, i++ + UP_SPACE, 0 + LEFT_SPACE + col);
	wprintw(vm->visu.w_panel, "Press * for max speed");
	wmove(vm->visu.w_panel, i++ + UP_SPACE, 0 + LEFT_SPACE + col);
	wprintw(vm->visu.w_panel, "Press = for process details");
	wmove(vm->visu.w_panel, i++ + UP_SPACE, 0 + LEFT_SPACE + col);
	wprintw(vm->visu.w_panel, "Press 1 2 3 to change update type");
	wattroff(vm->visu.w_panel, COLOR_PAIR(NP_COLOR));
}

static void	visu_speed_two(t_vm *vm, int col, int i)
{
	wattroff(vm->visu.w_panel, COLOR_PAIR(RD_COLOR));
	wattron(vm->visu.w_panel, COLOR_PAIR(WH_COLOR));
	wmove(vm->visu.w_panel, i++ + UP_SPACE, 0 + LEFT_SPACE + col);
	wprintw(vm->visu.w_panel, "Update for every: ");
	wattroff(vm->visu.w_panel, COLOR_PAIR(WH_COLOR));
	wattron(vm->visu.w_panel, COLOR_PAIR(RD_COLOR));
	if (vm->visu.update_type == UPDATE_PC)
		wprintw(vm->visu.w_panel, "processus      ");
	else if (vm->visu.update_type == UPDATE_FUNC)
		wprintw(vm->visu.w_panel, "active function");
	else if (vm->visu.update_type == UPDATE_CYCLE)
		wprintw(vm->visu.w_panel, "cycle          ");
	wattroff(vm->visu.w_panel, COLOR_PAIR(RD_COLOR));
	wattron(vm->visu.w_panel, COLOR_PAIR(WH_COLOR));
	wmove(vm->visu.w_panel, i++ + UP_SPACE, 0 + LEFT_SPACE + col);
	wprintw(vm->visu.w_panel, "Slow factor : %10.1f", vm->visu.speed);
	wattroff(vm->visu.w_panel, COLOR_PAIR(WH_COLOR));
	wmove(vm->visu.w_panel, i++ + UP_SPACE, 0 + LEFT_SPACE + col);
	wmove(vm->visu.w_panel, i++ + UP_SPACE, 0 + LEFT_SPACE + col);
	wattron(vm->visu.w_panel, COLOR_PAIR(NP_COLOR));
	wprintw(vm->visu.w_panel, "Press - to slow player");
	wmove(vm->visu.w_panel, i++ + UP_SPACE, 0 + LEFT_SPACE + col);
	wprintw(vm->visu.w_panel, "Press + to speed player");
	visu_speed_three(vm, col, i);
}

void		visu_speed(t_vm *vm, int row, int col)
{
	int		i;

	i = row;
	wattron(vm->visu.w_panel, COLOR_PAIR(WH_COLOR));
	wmove(vm->visu.w_panel, i++ + UP_SPACE, 0 + LEFT_SPACE + col);
	wprintw(vm->visu.w_panel, "Corewar is ");
	wattroff(vm->visu.w_panel, COLOR_PAIR(WH_COLOR));
	wattron(vm->visu.w_panel, COLOR_PAIR(RD_COLOR));
	if (vm->visu.pause)
		wprintw(vm->visu.w_panel, "paused,     ");
	else
		wprintw(vm->visu.w_panel, "not paused, ");
	wattroff(vm->visu.w_panel, COLOR_PAIR(RD_COLOR));
	wattron(vm->visu.w_panel, COLOR_PAIR(WH_COLOR));
	wprintw(vm->visu.w_panel, "press space to change.");
	wmove(vm->visu.w_panel, i++ + UP_SPACE, 0 + LEFT_SPACE + col);
	wprintw(vm->visu.w_panel, "Process details are ");
	wattroff(vm->visu.w_panel, COLOR_PAIR(WH_COLOR));
	wattron(vm->visu.w_panel, COLOR_PAIR(RD_COLOR));
	if (vm->visu.proc)
		wprintw(vm->visu.w_panel, "refresh.    ");
	else
		wprintw(vm->visu.w_panel, "not refresh.");
	visu_speed_two(vm, col, i);
}
