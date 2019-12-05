/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 16:19:50 by gtaja             #+#    #+#             */
/*   Updated: 2019/11/01 18:36:14 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

int		main(int ac, char **av)
{
	t_vm	vm;

	if (ac > 1)
	{
		if (!init(&vm, ac, av))
			return (0);
		vm_cycle(&vm);
	}
	else
		usage_corewar();
	return (0);
}
