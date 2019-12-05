/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 20:28:27 by ldevelle          #+#    #+#             */
/*   Updated: 2019/11/02 21:38:03 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void			visu_process_type_arg(t_vm *vm, uint8_t type, int func)
{
	if (type & T_DIR)
	{
		if (g_op_tab[func].is_direct_two_bytes)
			wprintw(vm->visu.w_proc, "T_DIR(%d)", DIR_2B_SIZE);
		else
			wprintw(vm->visu.w_proc, "T_DIR(%d)", DIR_SIZE);
	}
	else if (type & T_REG)
		wprintw(vm->visu.w_proc, "T_REG   ", REGSTR_SIZE);
	else if (type & T_IND)
		wprintw(vm->visu.w_proc, "T_IND   ", IND_SIZE);
	else
		wprintw(vm->visu.w_proc, "        ", IND_SIZE);
}

void			visu_process_arg(t_vm *vm, t_process *process)
{
	int			i;
	int			col;
	int			arg_number;

	i = 5 + 2;
	col = 50;
	arg_number = 0;
	while (++arg_number <= 3)
		if (process->args.use[arg_number - 1])
		{
			wmove(vm->visu.w_proc, i++ + UP_SPACE, col + LEFT_SPACE);
			wprintw(vm->visu.w_proc, "arg[%d] :\t", arg_number - 1);
			visu_process_type_arg(vm, process->args.use[arg_number - 1],
				process->next_func - 1);
			wmove(vm->visu.w_proc, i++ + UP_SPACE, col + LEFT_SPACE);
			wprintw(vm->visu.w_proc, "\t\traw: %-10d",
				process->args.raw[arg_number - 1]);
			wmove(vm->visu.w_proc, i++ + UP_SPACE, col + LEFT_SPACE);
			wprintw(vm->visu.w_proc, "\t\tdir: %-10d",
				process->args.dir[arg_number - 1]);
			wmove(vm->visu.w_proc, i++ + UP_SPACE, col + LEFT_SPACE);
			wprintw(vm->visu.w_proc, "\t\tidx: %-10d",
				process->args.idx[arg_number - 1]);
			i++;
		}
}

void			visu_process_reg(t_process *process)
{
	int			i;
	uint8_t		reg;

	i = -1;
	while (++i < REG_NUMBER)
	{
		wmove(process->vm->visu.w_proc, i + 6 + UP_SPACE, LEFT_SPACE + 5);
		wprintw(process->vm->visu.w_proc, "REG[%02d]: ", i + 1);
		ft_memmove(&reg, process->registre + (i * REG_SIZE) + 0, 1);
		wprintw(process->vm->visu.w_proc, "%02hhx", reg);
		ft_memmove(&reg, process->registre + (i * REG_SIZE) + 1, 1);
		wprintw(process->vm->visu.w_proc, " %02hhx", reg);
		ft_memmove(&reg, process->registre + (i * REG_SIZE) + 2, 1);
		wprintw(process->vm->visu.w_proc, " %02hhx", reg);
		ft_memmove(&reg, process->registre + (i * REG_SIZE) + 3, 1);
		wprintw(process->vm->visu.w_proc, " %02hhx", reg);
	}
}

void			visu_process_head(t_process *process)
{
	t_vm		*vm;
	int			i;

	vm = process->vm;
	i = 0;
	wmove(vm->visu.w_proc, i++ + UP_SPACE, 30 + LEFT_SPACE);
	wprintw(vm->visu.w_proc, "%-*s", 20, process->owner->name);
	wmove(vm->visu.w_proc, ++i + UP_SPACE, LEFT_SPACE);
	wprintw(vm->visu.w_proc, " ID:\t\t%*2d/%-*2d", 9, process->num, 9,
		process->vm->tt_pc);
	wmove(vm->visu.w_proc, i++ + UP_SPACE, 60 + LEFT_SPACE);
	wprintw(vm->visu.w_proc, "PC:\t%-*d", 10, process->pc);
	wmove(vm->visu.w_proc, i + UP_SPACE, LEFT_SPACE);
	wprintw(vm->visu.w_proc, " Timer:\t%-*d", 20, process->timer);
	wmove(vm->visu.w_proc, i++ + UP_SPACE, 60 + LEFT_SPACE);
	wprintw(vm->visu.w_proc, "Carry:\t%-*d", 10, process->carry);
	wmove(vm->visu.w_proc, i + UP_SPACE, 60 + LEFT_SPACE);
	wprintw(vm->visu.w_proc, "Lives:\t%-*d", 10, process->lives_since_check);
	wmove(vm->visu.w_proc, i++ + UP_SPACE, LEFT_SPACE);
	if (process->timer >= 0)
		wprintw(vm->visu.w_proc, " Next func:\t%-*s", 20,
			g_op_tab[process->next_func - 1].name);
	else
		wprintw(vm->visu.w_proc, " Next func:\t%-*s", 20, " ");
}

void			visu_update_process(t_process *process)
{
	t_vm		*vm;

	vm = process->vm;
	if (process->timer != 0)
	{
		visu_erase(vm, V_PROC);
		wborder(vm->visu.w_proc, '|', '|', '-', '-', '+', '+', '+', '+');
	}
	wattron(vm->visu.w_proc, COLOR_PAIR(process->owner->number));
	if (process->timer == 0)
		visu_process_arg(vm, process);
	visu_process_reg(process);
	visu_process_head(process);
	wattroff(vm->visu.w_proc, COLOR_PAIR(process->owner->number));
}
