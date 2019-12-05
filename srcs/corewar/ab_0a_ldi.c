/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ab_0a_ldi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 15:04:52 by lpoinsot          #+#    #+#             */
/*   Updated: 2019/11/03 07:51:22 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

static void	sum_calculation(t_args *args, int32_t sum[3], int16_t small_sum[3])
{
	int		i;

	if (args->use[0] == T_DIR)
		small_sum[0] = args->deu[0];
	else
		sum[0] = args->dir[0];
	if (args->use[1] == T_DIR)
		small_sum[1] = args->deu[1];
	else
		sum[1] = args->dir[1];
	i = 0;
	while (i < 2)
	{
		sum[2] += small_sum[i];
		sum[2] += sum[i];
		i++;
	}
}

static int	get_ldi_pos(t_process *process, t_args *args, int32_t sum[3],
				int16_t small_sum[3])
{
	int			position;

	if (args->use[0] == T_DIR && args->use[1] == T_DIR)
	{
		small_sum[0] = args->deu[0] + args->deu[1];
		position = pc_access_short(process->pc, small_sum[0], PC_RESTRICT);
	}
	else
	{
		sum_calculation(args, sum, small_sum);
		position = pc_access(process->pc, sum[2], PC_RESTRICT);
	}
	return (position);
}

static void	ldi_smallprint(t_process *process, t_args *args, int i)
{
	ft_printf("P %4d |", process->num);
	ft_printf(" ldi");
	while (i < 3)
	{
		if (i == 2)
			ft_printf(" r%d", args->raw[i]);
		else
			ft_printf(" %d", (int16_t)args->dir[i]);
		i++;
	}
	ft_printf("\n");
	ft_printf("       | -> load from");
}

static void	ldi_verbose(t_process *process, t_args *args, int32_t sum[3],
				int16_t small_sum[3])
{
	int		i;

	i = 0;
	ldi_smallprint(process, args, i);
	while (i < 2)
	{
		ft_printf(" %d ", (int16_t)args->dir[i]);
		i++;
		i == 1 ? ft_printf("+") : ft_printf("= ");
	}
	if (args->use[0] == T_DIR && args->use[1] == T_DIR)
	{
		ft_printf("%d ", small_sum[0]);
		ft_printf("(with pc and mod %d)\n", (int32_t)((int32_t)process->pc
			+ (int16_t)small_sum[0]));
	}
	else
	{
		ft_printf("%d ", sum[2]);
		ft_printf("(with pc and mod %d)\n", (int32_t)((int32_t)process->pc
			+ (int16_t)sum[2]));
	}
}

int			ldi(t_vm *vm, t_process *process, t_args *args)
{
	int			position;
	int32_t		sum[3];
	int16_t		small_sum[3];
	int			i;

	i = 0;
	while (i < 3)
	{
		sum[i] = 0;
		small_sum[i] = 0;
		i++;
	}
	position = get_ldi_pos(process, args, sum, small_sum);
	if (vm->options.verbose)
		ldi_verbose(process, args, sum, small_sum);
	write_registre(process, args->idx[2], read_vm_int(vm, position));
	return (SUCCESS);
}
