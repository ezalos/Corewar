/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ab_0b_sti.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 15:04:58 by lpoinsot          #+#    #+#             */
/*   Updated: 2019/11/03 07:51:22 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

static void	sum_calc(t_args *args, int32_t sum[3], int16_t small_sum[3])
{
	int			i;

	if (args->use[1] == T_DIR)
		small_sum[1] = args->deu[1];
	else
		sum[1] = args->dir[1];
	if (args->use[2] == T_DIR)
		small_sum[2] = args->deu[2];
	else
		sum[2] = args->dir[2];
	i = 1;
	while (i < 3)
	{
		sum[0] += small_sum[i];
		sum[0] += sum[i];
		i++;
	}
}

static int	get_sti_pos(t_process *process, t_args *args, int32_t sum[3],
				int16_t small_sum[3])
{
	int			position;

	if (args->use[1] == T_DIR && args->use[2] == T_DIR)
	{
		small_sum[0] = args->deu[1] + args->deu[2];
		position = pc_access_short(process->pc, small_sum[0], PC_RESTRICT);
	}
	else
	{
		sum_calc(args, sum, small_sum);
		position = pc_access(process->pc, sum[0], PC_RESTRICT);
	}
	return (position);
}

static void	sti_small_print(t_process *process, t_args *args, int i)
{
	ft_printf("P %4d |", process->num);
	ft_printf(" sti");
	while (i < 3)
	{
		if (!i)
			ft_printf(" r%d", args->raw[i]);
		else
			ft_printf(" %d", (int16_t)args->dir[i]);
		i++;
	}
	ft_printf("\n");
	ft_printf("       | -> store to");
}

static void	sti_verbose(t_process *process, t_args *args, int32_t sum[3],
				int16_t small_sum[3])
{
	int			i;

	sti_small_print(process, args, 0);
	i = 1;
	while (i < 3)
	{
		ft_printf(" %d ", (int16_t)args->dir[i]);
		i++;
		if (i == 2)
			ft_printf("+");
		else
			ft_printf("= ");
	}
	if (args->use[1] == T_DIR && args->use[2] == T_DIR)
	{
		ft_printf("%d ", small_sum[0]);
		ft_printf("(with pc and mod %d)\n", (int32_t)((int32_t)process->pc
			+ ((int16_t)small_sum[0] % IDX_MOD)));
	}
	else
	{
		ft_printf("%d ", sum[0]);
		ft_printf("(with pc and mod %d)\n", (int32_t)((int32_t)process->pc
			+ (sum[0] % IDX_MOD)));
	}
}

int			sti(t_vm *vm, t_process *process, t_args *args)
{
	int32_t		sum[3];
	int16_t		small_sum[3];
	int			position;
	int			i;

	i = 0;
	while (i < 3)
	{
		small_sum[i] = 0;
		sum[i] = 0;
		i++;
	}
	position = get_sti_pos(process, args, sum, small_sum);
	if (vm->options.verbose)
		sti_verbose(process, args, sum, small_sum);
	write_possess(vm, position, process->owner->number, REG_SIZE);
	write_vm(vm, position, &args->dir[0], REG_SIZE);
	return (SUCCESS);
}
