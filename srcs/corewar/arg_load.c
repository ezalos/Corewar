/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 21:44:20 by ldevelle          #+#    #+#             */
/*   Updated: 2019/11/04 00:42:25 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

uint8_t		is_pc_restrict(uint8_t function_code)
{
	if (function_code == 0x01
	|| function_code == 0x04
	|| function_code == 0x05
	|| function_code == 0x0d
	|| function_code == 0x0f
	|| function_code == 0x10)
		return (FAILURE);
	if (function_code == 0x02
	|| function_code == 0x03
	|| function_code == 0x06
	|| function_code == 0x07
	|| function_code == 0x08
	|| function_code == 0x09
	|| function_code == 0x0a
	|| function_code == 0x0b
	|| function_code == 0x0c
	|| function_code == 0x0e)
		return (SUCCESS);
	return (SUCCESS);
}

int8_t		arg_load_type_dir(t_vm *vm, t_process *process, int32_t arg,
			uint8_t arg_number)
{
	(void)vm;
	process->args.deu[arg_number - 1] = (int16_t)arg;
	process->args.dir[arg_number - 1] = arg;
	return (SUCCESS);
}

int8_t		arg_load_type_reg(t_process *process, int32_t arg,
			uint8_t arg_number)
{
	int8_t	ret;

	if (arg > REG_NUMBER || arg < 1)
		ret = FAILURE;
	else
	{
		process->args.idx[arg_number - 1] = arg - 1;
		ft_memmove(&process->args.dir[arg_number - 1],
			&process->registre[process->args.idx[arg_number - 1] * REG_SIZE],
			REG_SIZE);
		change_endian(process->args.dir + (arg_number - 1), sizeof(int32_t));
		ret = SUCCESS;
	}
	return (ret);
}

int8_t		arg_load_type_ind(t_vm *vm, t_process *process,
			int32_t arg, uint8_t arg_number)
{
	uint32_t	position;

	position = pc_access_short(process->pc, (int16_t)arg,
		is_pc_restrict(process->next_func));
	process->args.idx[arg_number - 1] = position;
	process->args.dir[arg_number - 1] = read_vm_int(vm, position);
	process->args.deu[arg_number - 1] = (int16_t)arg;
	return (SUCCESS);
}

int8_t		load_args_in_struct(t_vm *vm, t_process *process)
{
	t_arg_type	arg_type;
	int32_t		arg;
	uint8_t		arg_number;
	int8_t		ret;

	ret = FAILURE;
	arg_number = 0;
	ft_bzero(&process->args, sizeof(t_args));
	while (++arg_number <= g_op_tab[process->next_func - 1].nb_args)
	{
		arg = return_arg(vm, process, arg_number);
		arg_type = get_arg_type(vm, process, arg_number);
		process->args.raw[arg_number - 1] = arg;
		process->args.use[arg_number - 1] = arg_type;
		if (arg_type == T_DIR)
			ret = arg_load_type_dir(vm, process, arg, arg_number);
		else if (arg_type == T_REG)
			ret = arg_load_type_reg(process, arg, arg_number);
		else if (arg_type == T_IND)
			ret = arg_load_type_ind(vm, process, arg, arg_number);
		if (ret == FAILURE)
			break ;
	}
	return (ret);
}
