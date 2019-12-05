/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aa_03_st.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 15:04:06 by lpoinsot          #+#    #+#             */
/*   Updated: 2019/11/04 00:35:26 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

int			st(t_vm *vm, t_process *process, t_args *args)
{
	if (vm->options.verbose)
	{
		ft_printf("P %4d | st r%d %d\n", process->num, args->raw[0],
				args->use[1] == T_IND ? (int16_t)args->raw[1] : args->raw[1]);
	}
	if (args->use[1] == T_IND)
	{
		write_possess(vm, args->idx[1], process->owner->number, REG_SIZE);
		write_vm(vm, args->idx[1], &args->dir[0], REG_SIZE);
	}
	else if (args->idx[1] >= 0 && args->idx[1] < REG_NUMBER)
		write_registre(process, args->idx[1], args->dir[0]);
	else
		return (FAILURE);
	return (SUCCESS);
}
