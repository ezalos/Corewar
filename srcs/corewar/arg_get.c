/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 21:43:46 by ldevelle          #+#    #+#             */
/*   Updated: 2019/11/03 04:20:55 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

uint8_t			get_arg_type(t_vm *vm, t_process *process, uint8_t arg_number)
{
	uint8_t			arg_type;

	(void)vm;
	if (g_op_tab[process->next_func - 1].need_ocp)
		arg_type = get_arg_type_ocp(process->ocp, arg_number);
	else if (arg_number == 1)
		arg_type = T_DIR;
	else
		arg_type = 0;
	return (arg_type);
}

uint32_t		get_arg_size(t_vm *vm, t_process *process, uint8_t arg_number)
{
	t_arg_type		arg_type;

	arg_type = 0;
	if (arg_number >= 1 && arg_number <= 3)
	{
		arg_type = get_arg_type(vm, process, arg_number);
		if (arg_type == T_IND)
			return (IND_SIZE);
		else if (arg_type == T_REG)
			return (REGSTR_SIZE);
		else if (arg_type == T_DIR)
		{
			if (g_op_tab[process->next_func - 1].is_direct_two_bytes)
				return (DIR_2B_SIZE);
			else
				return (DIR_SIZE);
		}
	}
	return (0);
}

uint32_t		get_arg_position(t_vm *vm, t_process *process,
					uint8_t arg_number)
{
	uint32_t	position;

	position = 0;
	if (arg_number == 0 || arg_number > 4)
		return (0);
	else if (arg_number == 1)
		return (1 + g_op_tab[process->next_func - 1].need_ocp);
	if (arg_number > 1)
		position += get_arg_size(vm, process, arg_number - 1);
	position += get_arg_position(vm, process, arg_number - 1);
	return (position);
}

int32_t			return_arg(t_vm *vm, t_process *process, uint8_t arg_number)
{
	int32_t		arg;
	uint32_t	arg_position_in_mem;
	uint32_t	arg_size;

	arg_size = get_arg_size(vm, process, arg_number);
	arg_position_in_mem = get_arg_position(vm, process, arg_number);
	arg = 0;
	read_vm(vm, process->pc + arg_position_in_mem, &arg, arg_size);
	return (arg);
}
