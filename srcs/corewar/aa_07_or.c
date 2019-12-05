/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aa_07_or.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 15:04:32 by lpoinsot          #+#    #+#             */
/*   Updated: 2019/11/03 07:51:22 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

int			or_(t_vm *vm, t_process *process, t_args *args)
{
	int			i;
	uint32_t	result;

	(void)vm;
	if (vm->options.verbose)
	{
		ft_printf("P %4d | or", process->num);
		i = -1;
		while (++i < 3)
		{
			ft_printf(" ");
			if (i == 2)
				ft_printf("r%d", args->raw[i]);
			else
				ft_printf("%d", args->dir[i]);
		}
		ft_printf("\n");
	}
	result = args->dir[0] | args->dir[1];
	write_registre(process, args->idx[2], result);
	process->carry = !result;
	return (SUCCESS);
}
