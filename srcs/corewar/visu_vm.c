/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 20:26:17 by ldevelle          #+#    #+#             */
/*   Updated: 2019/11/02 16:21:46 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void		visu_vm_coord(t_vm *vm, int pos)
{
	wmove(vm->visu.w_vm, (((pos) % MEM_SIZE) / 64) + 0 + UP_SPACE,
		1 + (((pos) % 64) * 3) + LEFT_SPACE);
}

void		visu_update_pc(t_vm *vm, int pos, int type)
{
	if (vm->visu.visu
	&& ((vm->visu.update_type != UPDATE_PC && type != PC_ACTIF)
	|| vm->visu.update_type == UPDATE_PC || vm->visu.pause))
	{
		(pos < 0) ? pos = -pos : 0;
		visu_vm_coord(vm, pos);
		if (type == PC_CREATE)
			wattron(vm->visu.w_vm, COLOR_PAIR(PC_TMP_COLOR));
		else if (type == PC_DELETE)
			wattron(vm->visu.w_vm, COLOR_PAIR(vm->possess[pos % MEM_SIZE]));
		else if (type == PC_ACTIF)
			wattron(vm->visu.w_vm, COLOR_PAIR(AC_COLOR));
		wprintw(vm->visu.w_vm, "%02hhx", vm->mem[pos % MEM_SIZE]);
		if (type == PC_CREATE)
			wattroff(vm->visu.w_vm, COLOR_PAIR(PC_TMP_COLOR));
		else if (type == PC_DELETE)
			wattroff(vm->visu.w_vm, COLOR_PAIR(vm->possess[pos % MEM_SIZE]));
		else if (type == PC_ACTIF)
			wattroff(vm->visu.w_vm, COLOR_PAIR(AC_COLOR));
		if (vm->visu.update_type == UPDATE_PC || vm->visu.pause)
			wrefresh(vm->visu.w_vm);
		if (vm->visu.update_type == UPDATE_PC || vm->visu.pause)
			refresh();
	}
}

void		visu_update_vm(t_vm *vm, int pos, unsigned char *data, int size)
{
	int		color;
	int		i;

	(void)data;
	if (vm->visu.visu && (i = -1))
	{
		wattroff(vm->visu.w_vm, COLOR_PAIR(NP_COLOR));
		wborder(vm->visu.w_vm, '|', '|', '-', '-', '+', '+', '+', '+');
		wattron(vm->visu.w_vm, COLOR_PAIR(NP_COLOR));
		visu_vm_coord(vm, pos);
		color = vm->possess[pos % MEM_SIZE];
		wattron(vm->visu.w_vm, COLOR_PAIR(color));
		while (++i < size)
		{
			(!((pos + i) % 64)) ? visu_vm_coord(vm, pos + i) : 0;
			if (color != vm->possess[(pos + i) % MEM_SIZE])
			{
				wattroff(vm->visu.w_vm, COLOR_PAIR(color));
				color = vm->possess[(pos + i) % MEM_SIZE];
				wattron(vm->visu.w_vm, COLOR_PAIR(color));
			}
			wprintw(vm->visu.w_vm, "%02hhx ", vm->mem[(pos + i) % MEM_SIZE]);
		}
		wattroff(vm->visu.w_vm, COLOR_PAIR(color));
	}
}
