/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cycle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 19:55:09 by ldevelle          #+#    #+#             */
/*   Updated: 2019/12/24 15:08:14 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void		print_move_pc(t_vm *vm, t_process *process)
{
	int		len_func;
	// int		pos_next;
	int		i;

	if (vm->options.verbose == 0)
		return ;
	process->ocp = vm->mem[(process->pc + 1) % MEM_SIZE];
	len_func = get_arg_position(vm, process,
		g_op_tab[process->next_func - 1].nb_args + 1);
	// pos_next = pc_access(process->pc, len_func, NOT_PC_RESTRICT);
	ft_printf("ADV %d (0x%04x -> 0x%04x) ", len_func,
		process->pc, process->pc + len_func);
	i = -1;
	while (++i < len_func)
	{
		ft_printf("%02hhx ", vm->mem[(process->pc + i) % MEM_SIZE]);
	}
	ft_printf("\n");
}

int			process_exe_norm(t_vm *vm, t_process *process)
{
	call_visu(vm, process, UPDATE_PC);
	process->ocp = vm->mem[(process->pc + 1) % MEM_SIZE];
	print_move_pc(vm, process);
	move_pc(process, get_arg_position(vm, process,
		g_op_tab[process->next_func - 1].nb_args + 1), 0);
	return (SUCCESS);
}

int			process_exec_func(t_vm *vm, t_process *process)
{
	int			ret;

	if (check_ocp(process->next_func,
		vm->mem[(process->pc + 1) % MEM_SIZE]))
	{
		process->ocp = vm->mem[(process->pc + 1) % MEM_SIZE];
		ret = load_args_in_struct(vm, process);
		call_visu(vm, process, UPDATE_PC);
		if (ret == SUCCESS)
		{
			call_visu(vm, process, UPDATE_FUNC);
			call_function(vm, process);
		}
		if (process->next_func != 0x09 || !process->carry)
		{
			print_move_pc(vm, process);
			move_pc(process, get_arg_position(vm, process,
				g_op_tab[process->next_func - 1].nb_args + 1), 0);
		}
	}
	else
		ret = process_exe_norm(vm, process);
	return (ret);
}

t_process	*ret_proc(t_vm *vm, t_process *process)
{
	call_visu(vm, process, UPDATE_PC);
	visu_update_pc(process->vm, process->pc, PC_CREATE);
	process->timer--;
	process = process->next;
	return (process);
}

int			process_cycle(t_vm *vm)
{
	t_process	*process;
	int			ret;

	vm->current_p = vm->tt_pc;
	process = vm->process_start;
	while (process)
	{
		ret = SUCCESS;
		visu_update_pc(process->vm, process->pc, PC_ACTIF);
		call_visu(vm, process, 0);
		if (process->timer <= -1)
			process_get_func(vm, process);
		else if (process->timer == 0)
			ret = process_exec_func(vm, process);
		process = ret_proc(vm, process);
	}
	return (ret);
}
