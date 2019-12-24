/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 16:45:25 by gtaja             #+#    #+#             */
/*   Updated: 2019/12/24 15:07:22 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

int				get_dump_and_v(t_options *options, int ac, char **av, int *i)
{
	if (ft_strequ("-dump", av[*i]))
	{
		if (*i == ac - 1)
			return (usage_corewar());
		*i = *i + 1;
		if ((options->dump_cycles = ft_atoi(av[*i])) < 0)
		{
			ft_putendl_fd("--dump <nbr_cycles>: need positive number", 2);
			return (0);
		}
		return (-1);
	}
	else
		return (norm_dump(options, ac, av, i));
}

static int		show_error_if_need(int champ_number,
	int force)
{
	if (force)
	{
		if (champ_number > MAX_PLAYERS)
		{
			ft_putstr_fd("Les numeros des champions sont limité de 1 à ", 2);
			ft_putnbr_fd(MAX_PLAYERS, 2);
			ft_putstr_fd("\n", 2);
			return (0);
		}
		return (champ_number);
	}
	return (WAIT_POS);
}

int				set_champ_number(t_options *options, int ac, char **av, int *i)
{
	int			champ_number;
	int			force;

	champ_number = -1;
	force = FALSE;
	if (ft_strequ("-n", av[*i]))
	{
		if (*i >= ac - 2 || (champ_number = ft_atoi(av[*i + 1])) <= 0)
			return (usage_corewar());
		if (!options->available[champ_number - 1])
		{
			ft_putendl_fd("Deux champions ne peuvent avoir le meme numero", 2);
			return (0);
		}
		options->available[champ_number - 1] = 0;
		*i = *i + 2;
		force = TRUE;
	}
	return (show_error_if_need(champ_number, force));
}

static int		finish_assignment(t_options *options, int i, int j)
{
	while (++i < options->nb_champ)
	{
		if (options->number_champ[i] == WAIT_POS)
		{
			j = -1;
			while (++j < MAX_PLAYERS)
			{
				if (options->available[j])
				{
					options->number_champ[i] = j + 1;
					options->available[j] = 0;
					break ;
				}
			}
			if (options->number_champ[i] == WAIT_POS)
			{
				ft_putstr_fd("Nombre de champions maximum dépassé (MAX ", 2);
				ft_putnbr_fd(MAX_PLAYERS, 2);
				ft_putstr_fd(")\n", 2);
				return (0);
			}
		}
	}
	return (1);
}

int				init_arg_management(t_options *options, int ac, char **av)
{
	ft_memset(options->available, 1, sizeof(int) * MAX_PLAYERS);
	options->dump_cycles = -1;
	options->visu_break = -1;
	if (!arg_loop(options, ac, av))
		return (0);
	if (!options->nb_champ)
		return (usage_corewar());
	return (finish_assignment(options, -1, -1));
}
