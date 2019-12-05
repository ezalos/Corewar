/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage_corewar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 17:52:38 by gtaja             #+#    #+#             */
/*   Updated: 2019/11/04 00:01:43 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

int	usage_corewar(void)
{
	ft_putendl("How to use:");
	ft_putstr("./corewar [--dump nbr_cycles] [-v [cycle_break]] ");
	ft_putendl("[[-n number] champion1.cor] ...");
	ft_putendl("\t--dump: dump the VM's memmory after nbr_cycles");
	ft_putendl("\t-v: Visual option (it's cute <3) and pause at cycle_break");
	ft_putstr("\t-n: define a specific champion number (please pick a ");
	ft_printf("different number for each champions, between 1 and %d)\n",
		MAX_PLAYERS);
	ft_putendl("\t-mute: mute all champion's live");
	ft_putendl("\t-log: mystical verbose");
	return (0);
}
