/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 14:06:17 by ldevelle          #+#    #+#             */
/*   Updated: 2019/11/03 18:38:52 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void	init_fct_tab(t_vm *vm)
{
	vm->fct[0] = live;
	vm->fct[1] = ld;
	vm->fct[2] = st;
	vm->fct[3] = add;
	vm->fct[4] = sub;
	vm->fct[5] = and_;
	vm->fct[6] = or_;
	vm->fct[7] = xor_;
	vm->fct[8] = zjmp;
	vm->fct[9] = ldi;
	vm->fct[10] = sti;
	vm->fct[11] = fork_;
	vm->fct[12] = lld;
	vm->fct[13] = lldi;
	vm->fct[14] = lfork;
	vm->fct[15] = aff;
	vm->fct[16] = NULL;
}

void	init_vm(t_vm *vm)
{
	int		i;

	ft_bzero(vm, sizeof(t_vm));
	i = -1;
	while (++i < MAX_PLAYERS)
		ft_bzero(&(vm->champions[i]), sizeof(t_champion));
	init_fct_tab(vm);
	ft_memset(vm->possess, 5, MEM_SIZE);
}

void	init_visu(t_vm *vm)
{
	vm->visu.visu = 1;
	vm->visu.speed = SPEED_INIT;
	vm->visu.proc = 1;
	vm->visu.update_type = UPDATE_PC;
	if (vm->visu.visu)
	{
		init_ncurses(vm);
		visu_init_vm(vm);
	}
}

void	check_defines(void)
{
	int		error;

	error = 1;
	if (CYCLE_TO_DIE <= 0)
		ft_printf("%~.2CYCLE_TO_DIE <= 0\n");
	else if (CYCLE_DELTA <= 0)
		ft_printf("%~.2CYCLE_DELTA <= 0\n");
	else if (NBR_LIVE <= 0)
		ft_printf("%~.2NBR_LIVE <= 0\n");
	else if (MAX_CHECKS <= 0)
		ft_printf("%~.2MAX_CHECKS <= 0\n");
	else if (DUMP_CHAR_BY_LINE <= 0)
		ft_printf("%~.2DUMP_CHAR_BY_LINE <= 0\n");
	else
		error = 0;
	if (error)
		exit(EXIT_FAILURE);
}

int		init(t_vm *vm, int ac, char **av)
{
	int		i;
	int		champ_nb;

	check_defines();
	init_vm(vm);
	if (!init_arg_management(&(vm->options), ac, av))
		return (0);
	i = -1;
	champ_nb = 0;
	while (++i < vm->options.nb_champ)
	{
		if (read_cor_champ(vm,
			&(vm->champions[vm->options.number_champ[champ_nb] - 1]),
			champ_nb) == SUCCESS)
		{
			vm->champions[vm->options.number_champ[champ_nb] - 1].alive = TRUE;
			champ_nb++;
		}
	}
	vm->cycle = 1;
	vm->current_cycle = 1;
	return (1);
}
