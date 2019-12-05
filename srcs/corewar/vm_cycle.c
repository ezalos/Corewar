/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_cycle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 18:53:59 by ldevelle          #+#    #+#             */
/*   Updated: 2019/11/04 01:18:36 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

int			nb_players_alive(t_vm *vm)
{
	int		i;
	int		total_alive;

	total_alive = 0;
	i = -1;
	while (++i < vm->options.nb_champ)
		if (vm->champions[vm->options.number_champ[i] - 1].alive == TRUE)
			total_alive++;
	return (total_alive);
}

void		update_cycle_to_die(t_vm *vm)
{
	if (vm->max_checks >= MAX_CHECKS || vm->total_live_since_check >= NBR_LIVE)
	{
		vm->max_checks = 0;
		vm->cycle_to_die = vm->cycle_to_die - CYCLE_DELTA;
		if (vm->options.verbose == 1)
			ft_printf("Cycle to die is now %d\n", (int)((int)vm->cycle_to_die));
	}
	else
		vm->max_checks++;
	vm->total_live_since_check = 0;
	vm->current_cycle = 0;
}

void		kill_weak_process(t_vm *vm)
{
	t_process	*cur;
	t_process	*prev;

	prev = NULL;
	cur = vm->process_start;
	while (cur != NULL)
	{
		if (cur->lives_since_check <= 0)
		{
			if (vm->process_start == cur)
				vm->process_start = cur->next;
			if (vm->options.verbose)
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
					(int)cur->num, (int)((int)vm->cycle - (int)cur->last_live),
					vm->cycle_to_die);
			cur = rm_process_to_vm(cur, prev);
		}
		else
		{
			cur->lives_since_check = 0;
			prev = cur;
			cur = cur->next;
		}
	}
}

static void	dying_cycle_exe(t_vm *vm)
{
	kill_weak_process(vm);
	kill_weak_champ_allahu_akbar(vm);
	update_cycle_to_die(vm);
}

int			vm_cycle(t_vm *vm)
{
	if (vm->options.visu)
		init_visu(vm);
	vm->cycle_to_die = CYCLE_TO_DIE;
	while (vm->options.dump_cycles != 0 && vm->process_start != NULL)
	{
		if (vm->options.verbose)
			ft_printf("It is now cycle %lu\n", vm->cycle);
		call_visu(vm, NULL, UPDATE_CYCLE);
		process_cycle(vm);
		if (vm->process_start == NULL)
			break ;
		if (vm->cycle && vm->current_cycle >= vm->cycle_to_die)
			dying_cycle_exe(vm);
		if (vm->options.dump_cycles == (int32_t)vm->cycle)
			break ;
		vm->cycle++;
		vm->current_cycle++;
		if (vm->cycle == (unsigned long)vm->options.visu_break)
			vm->visu.pause = 1;
	}
	if (vm->visu.visu)
		visu_print_outro(vm);
	print_end(vm);
	return (0);
}
