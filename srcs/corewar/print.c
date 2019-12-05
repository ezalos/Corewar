/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpoinsot <lpoinsot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 18:19:38 by lpoinsot          #+#    #+#             */
/*   Updated: 2019/11/03 18:32:46 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void		print_octet(uint8_t nb)
{
	char		*base;

	base = "0123456789abcdef";
	if (!nb)
		ft_putstr("00");
	else if (nb < 16)
	{
		ft_putchar('0');
		ft_putchar(base[nb]);
	}
	else
		put_nbr_hex(nb, base);
}

void		print_dump(t_vm *vm)
{
	int			i;
	int			j;

	i = 0;
	while (i < (MEM_SIZE / DUMP_CHAR_BY_LINE))
	{
		ft_printf("0x%04x : ", i * DUMP_CHAR_BY_LINE);
		j = 0;
		while (j < DUMP_CHAR_BY_LINE)
		{
			print_octet(vm->mem[i * DUMP_CHAR_BY_LINE + j]);
			ft_putchar(' ');
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}

void		print_champ_name(t_champion *champ)
{
	ft_putnbr(champ->number);
	ft_putchar('(');
	ft_putstr(champ->name);
	ft_putchar(')');
}

void		free_all_processes(t_vm *vm)
{
	t_process	*free;
	t_process	*tmp;

	free = vm->process_start;
	while (free)
	{
		if (vm->options.verbose)
			ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
				(int)free->num, (int)((int)vm->cycle - (int)free->last_live),
				vm->cycle_to_die);
		tmp = free->next;
		ft_memdel((void**)&free);
		free = tmp;
	}
	vm->process_start = NULL;
	vm->tt_pc = 0;
}

void		print_end(t_vm *vm)
{
	if (vm->options.dump_cycles >= 0)
	{
		free_all_processes(vm);
		if (vm->options.dump_cycles != (int)vm->cycle
		&& vm->options.dump_cycles != 0)
		{
			ft_putstr("End of game before DUMP option at cycle : ");
			ft_putnbr(vm->cycle);
			ft_putendl("\nHere is the Hexdump at the final state of the VM: ");
		}
		ft_putstr("== HEXDUMP ==\n");
		print_dump(vm);
		ft_putchar('\n');
	}
	if (!vm->options.verbose)
	{
		ft_putstr("And the winner iiiiiiis : ");
		if (vm->last_alive_champ)
			print_champ_name(vm->last_alive_champ);
		else
			ft_putstr("NOBODY FUCKERS");
		ft_putchar('\n');
	}
}
