/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aa_02_ld.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 15:03:59 by lpoinsot          #+#    #+#             */
/*   Updated: 2019/11/03 07:51:22 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

int			ld(t_vm *vm, t_process *process, t_args *args)
{
	if (args->use[0] == T_IND)
		write_registre(process, args->idx[1], read_vm_int(vm, args->idx[0]));
	else
		write_registre(process, args->idx[1], args->dir[0]);
	process->carry = (args->dir[0] == 0);
	if (vm->options.verbose)
	{
		ft_printf("P %4d | ld %d r%d\n", process->num, args->dir[0],
			args->raw[1]);
	}
	return (SUCCESS);
}
