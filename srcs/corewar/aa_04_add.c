/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aa_04_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 15:04:14 by lpoinsot          #+#    #+#             */
/*   Updated: 2019/11/03 07:51:22 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

int			add(t_vm *vm, t_process *process, t_args *args)
{
	uint32_t	sum;

	(void)vm;
	if (vm->options.verbose)
	{
		ft_printf("P %4d | add r%d r%d r%d\n", process->num, args->raw[0],
			args->raw[1], args->raw[2]);
	}
	sum = args->dir[0] + args->dir[1];
	write_registre(process, args->idx[2], sum);
	process->carry = !sum;
	return (SUCCESS);
}
