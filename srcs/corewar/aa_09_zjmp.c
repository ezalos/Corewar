/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aa_09_zjmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 15:04:46 by lpoinsot          #+#    #+#             */
/*   Updated: 2019/11/04 00:36:23 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

int			zjmp(t_vm *vm, t_process *process, t_args *args)
{
	(void)vm;
	args->dir[0] = pc_access_short(0, args->dir[0], PC_RESTRICT);
	if (vm->options.verbose)
		ft_printf("P %4d | zjmp %d %s\n", process->num, (int16_t)args->raw[0],
			(process->carry) ? "OK" : "FAILED");
	if (process->carry)
	{
		move_pc(process, args->dir[0], 1);
		return (SUCCESS);
	}
	return (FAILURE);
}
