/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   am_long_direct_load.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoinsot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 15:05:13 by lpoinsot          #+#    #+#             */
/*   Updated: 2019/11/01 15:05:14 by lpoinsot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

int			lld(t_vm *vm, t_process *process, t_args *args)
{
	int		position;

	if (args->use[0] == T_IND)
	{
		position = args->idx[0];
		write_registre(process, args->idx[1], read_vm_int(vm, position));
	}
	else
		write_registre(process, args->idx[1], args->dir[0]);
	process->carry = (args->dir[0] == 0);
	return (SUCCESS);
}
