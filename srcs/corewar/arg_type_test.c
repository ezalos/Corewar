/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_type_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 15:25:06 by lpoinsot          #+#    #+#             */
/*   Updated: 2019/11/03 03:59:22 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

int					is_ok_opcode(unsigned char opcode)
{
	return (opcode < 17 && opcode > 0);
}

unsigned char		argument_bit_mask(t_uint arg_number)
{
	if (arg_number == 1)
		return (FIRST_ARG);
	if (arg_number == 2)
		return (SECOND_ARG);
	if (arg_number == 3)
		return (THIRD_ARG);
	if (arg_number == 4)
		return (FOURTH_ARG);
	return (0);
}

t_arg_type			get_arg_type_ocp(unsigned char arg_byte, t_uint arg_number)
{
	int				shift;

	arg_byte = arg_byte & argument_bit_mask(arg_number);
	shift = 6 - ((arg_number - 1) * 2);
	arg_byte = arg_byte >> shift;
	if (arg_byte == REG_CODE)
		return (T_REG);
	if (arg_byte == DIR_CODE)
		return (T_DIR);
	if (arg_byte == IND_CODE)
		return (T_IND);
	return (0);
}

int					is_ok_arg_type(unsigned char opcode, unsigned char arg_byte,
						t_uint arg_number)
{
	t_arg_type		type;

	type = get_arg_type_ocp(arg_byte, arg_number);
	if (arg_number > g_op_tab[opcode - 1].nb_args && type != 0)
		return (0);
	if (arg_number > g_op_tab[opcode - 1].nb_args && type == 0)
		return (1);
	return ((g_op_tab[opcode - 1].args_type[arg_number - 1] & type) != 0);
}

int					check_ocp(unsigned char opcode, unsigned char arg_byte)
{
	int				i;

	if (!is_ok_opcode(opcode))
		return (0);
	if (!g_op_tab[opcode - 1].need_ocp)
		return (1);
	i = 1;
	while (i <= (int)(g_op_tab[opcode - 1].nb_args))
	{
		if (!is_ok_arg_type(opcode, arg_byte, i))
			return (0);
		i++;
	}
	return (1);
}
