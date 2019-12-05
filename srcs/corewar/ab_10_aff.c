/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ab_10_aff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 15:05:30 by lpoinsot          #+#    #+#             */
/*   Updated: 2019/11/02 22:43:13 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

int			aff(t_vm *vm, t_process *process, t_args *args)
{
	char		c;

	(void)process;
	c = (char)(args->dir[0] % 256);
	if (!vm->visu.visu && !vm->options.mute)
		ft_putchar(c);
	return (SUCCESS);
}
