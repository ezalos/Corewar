/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 20:28:19 by ldevelle          #+#    #+#             */
/*   Updated: 2019/11/03 18:45:14 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void		init_ncurses(t_vm *vm)
{
	initscr();
	curs_set(0);
	if (has_colors() == FALSE)
	{
		endwin();
		ft_printf("%~.2Your terminal does not support color\n");
		exit(1);
	}
	start_color();
	vm->visu.w_head = newwin(H_HEAD, W_HEAD, UP_SPACE, LEFT_SPACE);
	vm->visu.w_vm = newwin(H_VM, W_VM, H_HEAD + UP_SPACE,
		LEFT_SPACE + SATYR_SPACE);
	vm->visu.w_panel = newwin(H_PANEL, W_PANEL, H_HEAD + UP_SPACE,
		W_VM + (LEFT_SPACE * 2) + SATYR_SPACE);
	vm->visu.w_proc = newwin(H_PROC, W_PROC, H_HEAD + H_PANEL + (UP_SPACE),
		W_VM + (LEFT_SPACE * 2) + SATYR_SPACE);
	visu_init_colors();
}

void		visu_init_colors(void)
{
	init_color(BK_COLOR, 100, 100, 100);
	init_color(NP_COLOR, 500, 500, 500);
	init_pair(NP_COLOR, NP_COLOR, BK_COLOR);
	init_color(RD_COLOR, 1000, 0, 0);
	init_pair(RD_COLOR, RD_COLOR, BK_COLOR);
	init_color(BW_COLOR, 141 * 4, 85 * 4, 36 * 4);
	init_pair(BW_COLOR, BW_COLOR, BK_COLOR);
	init_color(WH_COLOR, 1000, 1000, 1000);
	init_pair(WH_COLOR, WH_COLOR, BK_COLOR);
	init_color(GD_COLOR, 1000, 155 * 4, 0);
	init_pair(GD_COLOR, GD_COLOR, BK_COLOR);
	init_color(AC_COLOR, 1000, 1000, 0);
	init_pair(AC_COLOR, BK_COLOR, AC_COLOR);
	init_color(P1_COLOR, 1000, 450, 450);
	init_pair(P1_COLOR, P1_COLOR, BK_COLOR);
	init_color(P2_COLOR, 550, 550, 1000);
	init_pair(P2_COLOR, P2_COLOR, BK_COLOR);
	init_color(P3_COLOR, 350, 800, 350);
	init_pair(P3_COLOR, P3_COLOR, BK_COLOR);
	init_color(P4_COLOR, 900, 900, 350);
	init_pair(P4_COLOR, P4_COLOR, BK_COLOR);
	init_color(PC_TMP_COLOR, 600, 600, 600);
	init_pair(PC_TMP_COLOR, BK_COLOR, PC_TMP_COLOR);
}

void		visu_init_vm(t_vm *vm)
{
	if (vm->visu.visu)
	{
		visu_background(vm, V_V | V_VM | V_PROC | V_HEAD | V_PANEL);
		visu_refresh(vm, V_ALL);
		visu_refresh(vm, V_V);
		visu_print_intro(vm);
		visu_background(vm, V_V);
		visu_erase(vm, V_V);
		visu_refresh(vm, V_V);
		visu_update_vm(vm, 0, vm->mem, MEM_SIZE);
		visu_update_panel(vm);
		visu_update_head(vm);
	}
}
