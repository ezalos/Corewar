/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ab_0e_lldi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 15:05:19 by lpoinsot          #+#    #+#             */
/*   Updated: 2019/11/02 23:32:14 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

int			lldi(t_vm *vm, t_process *process, t_args *args)
{
	int32_t		sum;
	int16_t		small_sum;
	int			position;

	if (args->use[0] == T_DIR && args->use[1] == T_DIR)
	{
		small_sum = args->deu[0] + args->deu[1];
		position = pc_access_short(process->pc, small_sum, NOT_PC_RESTRICT);
	}
	else
	{
		sum = args->dir[0] + args->dir[1];
		position = pc_access(process->pc, sum, NOT_PC_RESTRICT);
	}
	write_registre(process, args->idx[2], read_vm_int(vm, position));
	process->carry = !(read_vm_int(vm, position));
	return (SUCCESS);
}
