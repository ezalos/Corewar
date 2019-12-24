/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aa_01_live.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoinsot <lpoinsot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 15:03:53 by lpoinsot          #+#    #+#             */
/*   Updated: 2019/12/24 15:06:32 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

static void	init_live(t_vm *vm, t_process *process)
{
	process->lives_since_check++;
	process->last_live = vm->cycle;
}

int			live(t_vm *vm, t_process *process, t_args *args)
{
	uint32_t		nb_champ;

	init_live(vm, process);
	vm->total_live_since_check++;
	nb_champ = (UINT_MAX - args->raw[0]);
	if (vm->options.verbose)
		ft_printf("P %4d | live %d\n", process->num, args->raw[0]);
	if (/*nb_champ >= 0 && */nb_champ < MAX_PLAYERS
		&& vm->champions[nb_champ].exist)
	{
		vm->champions[nb_champ].lives_since_check++;
		vm->champions[nb_champ].last_live_cycle = vm->cycle;
		vm->last_alive_champ = &(vm->champions[nb_champ]);
		if (!vm->visu.visu && !vm->options.verbose && !vm->options.mute)
		{
			ft_putstr("Un processus dit que le joueur ");
			print_champ_name(&vm->champions[nb_champ]);
			ft_putstr(" est en vie\n");
		}
		if (vm->options.verbose)
			ft_printf("Player %d (%s) is said to be alive\n",
				vm->champions[nb_champ].number, vm->champions[nb_champ].name);
		return (SUCCESS);
	}
	return (FAILURE);
}
