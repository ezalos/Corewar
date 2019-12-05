/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 21:13:03 by ldevelle          #+#    #+#             */
/*   Updated: 2019/10/31 12:56:46 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void		visu_background(t_vm *vm, uint8_t to_do)
{
	if (to_do & V_V)
		bkgd(COLOR_PAIR(NP_COLOR));
	if (to_do & V_VM)
		wbkgd(vm->visu.w_vm, COLOR_PAIR(NP_COLOR));
	if (to_do & V_PROC)
		wbkgd(vm->visu.w_proc, COLOR_PAIR(NP_COLOR));
	if (to_do & V_HEAD)
		wbkgd(vm->visu.w_head, COLOR_PAIR(NP_COLOR));
	if (to_do & V_PANEL)
		wbkgd(vm->visu.w_panel, COLOR_PAIR(NP_COLOR));
}

void		visu_border(t_vm *vm, uint8_t to_do)
{
	if (to_do & V_VM)
	{
		wborder(vm->visu.w_vm, '|', '|', '-', '-', '+', '+', '+', '+');
		wrefresh(vm->visu.w_vm);
	}
	if (to_do & V_PROC)
	{
		wborder(vm->visu.w_proc, '|', '|', '-', '-', '+', '+', '+', '+');
		wrefresh(vm->visu.w_proc);
	}
	if (to_do & V_HEAD)
	{
		wborder(vm->visu.w_head, '|', '|', '-', '-', '+', '+', '+', '+');
		wrefresh(vm->visu.w_head);
	}
	if (to_do & V_PANEL)
	{
		wborder(vm->visu.w_panel, '|', '|', '-', '-', '+', '+', '+', '+');
		wrefresh(vm->visu.w_panel);
	}
	if (to_do & V_V)
	{
		border('|', '|', '-', '-', '+', '+', '+', '+');
	}
	refresh();
}

void		visu_refresh(t_vm *vm, uint8_t to_do)
{
	if (to_do & V_VM)
		wrefresh(vm->visu.w_vm);
	if (to_do & V_PROC)
		wrefresh(vm->visu.w_proc);
	if (to_do & V_HEAD)
		wrefresh(vm->visu.w_head);
	if (to_do & V_PANEL)
		wrefresh(vm->visu.w_panel);
	if (to_do & V_V)
		refresh();
}

void		visu_erase(t_vm *vm, uint8_t to_do)
{
	if (to_do & V_VM)
		werase(vm->visu.w_vm);
	if (to_do & V_PROC)
		werase(vm->visu.w_proc);
	if (to_do & V_HEAD)
		werase(vm->visu.w_head);
	if (to_do & V_PANEL)
		werase(vm->visu.w_panel);
	if (to_do & V_V)
		erase();
}
