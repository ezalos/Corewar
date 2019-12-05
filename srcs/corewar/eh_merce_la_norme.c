/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eh_merce_la_norme.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoinsot <lpoinsot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 13:30:32 by lpoinsot          #+#    #+#             */
/*   Updated: 2019/11/03 18:44:50 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

int			process_get_func(t_vm *vm, t_process *process)
{
	int			ret;
	uint32_t	mem_cell;

	ret = FAILURE;
	mem_cell = vm->mem[process->pc % MEM_SIZE];
	if (mem_cell > 0 && mem_cell < 17)
	{
		process->timer = g_op_tab[mem_cell - 1].nb_cycle - 1;
		process->next_func = mem_cell;
		process->ocp = vm->mem[(process->pc + 1) % MEM_SIZE];
		ret = SUCCESS;
	}
	else
	{
		move_pc(process, 1, 0);
	}
	call_visu(vm, process, UPDATE_PC);
	return (ret);
}

int			call_function(t_vm *vm, t_process *process)
{
	int			ret;

	ret = (*vm->fct[process->next_func - 1])(vm, process, &process->args);
	return (ret);
}

void		kill_weak_champ_allahu_akbar(t_vm *vm)
{
	int i;

	i = -1;
	while (++i < vm->options.nb_champ)
	{
		if (!vm->champions[vm->options.number_champ[i] - 1].lives_since_check)
			vm->champions[vm->options.number_champ[i] - 1].alive = FALSE;
		else
			vm->champions[vm->options.number_champ[i] - 1].alive = TRUE;
		vm->champions[vm->options.number_champ[i] - 1].lives_since_check = 0;
	}
}

int			norm_dump(t_options *options, int ac, char **av, int *i)
{
	if (ft_strequ("-v", av[*i]))
	{
		if (ac > *i + 1 && !ft_strendswith(av[*i + 1], ".cor")
			&& (options->visu_break = ft_atoi(av[*i + 1])) > 0)
			*i = *i + 1;
		else
			options->visu_break = -1;
		options->visu = 1;
		return (-1);
	}
	else if (ft_strequ("-log", av[*i]))
	{
		options->verbose = 1;
		return (-1);
	}
	else if (ft_strequ("-mute", av[*i]))
	{
		options->mute = 1;
		return (-1);
	}
	return (1);
}

int			arg_loop(t_options *options, int ac, char **av)
{
	int		i;
	int		tmp;

	i = 0;
	while (++i < ac)
	{
		tmp = get_dump_and_v(options, ac, av, &i);
		if (tmp == 0)
			return (0);
		else if (tmp == -1)
			continue ;
		tmp = set_champ_number(options, ac, av, &i);
		if (tmp <= 0)
			return (0);
		options->number_champ[options->nb_champ] = tmp;
		options->path_champ[options->nb_champ] = av[i];
		options->nb_champ++;
		if (options->nb_champ > MAX_PLAYERS)
		{
			ft_printf("%~.2Nombre de champions maximum dépassé (MAX %d)\n",
				MAX_PLAYERS);
			return (0);
		}
	}
	return (1);
}
