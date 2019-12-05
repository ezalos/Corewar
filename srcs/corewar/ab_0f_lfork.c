/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ab_0f_lfork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 15:05:25 by lpoinsot          #+#    #+#             */
/*   Updated: 2019/11/04 01:23:09 by lpoinsot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

int			lfork(t_vm *vm, t_process *process, t_args *args)
{
	t_process		*new_process;

	(void)vm;
	new_process = copy_process(process);
	new_process->pc = pc_access_short(new_process->pc,
		(int16_t)args->raw[0], NOT_PC_RESTRICT);
	add_process_to_vm(vm, new_process);
	if (vm->options.verbose)
		ft_printf("P %4d | lfork %d (%d)\n", process->num,
			(int16_t)args->dir[0], ((int16_t)process->pc +
				(int16_t)args->dir[0]));
	return (SUCCESS);
}
