/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_access.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 21:45:21 by ldevelle          #+#    #+#             */
/*   Updated: 2019/11/01 16:29:12 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void		read_vm(t_vm *vm, uint32_t position, void *dest, uint32_t size)
{
	uint32_t	i;

	i = 0;
	while (i < size)
	{
		ft_memmove(dest + i, vm->mem + ((position + i) % MEM_SIZE), 1);
		i++;
	}
	change_endian(dest, size);
}

uint32_t	read_vm_int(t_vm *vm, uint32_t position)
{
	uint32_t	ret;

	read_vm(vm, position, &ret, sizeof(uint32_t));
	return (ret);
}

void		write_vm(t_vm *vm, uint32_t position, void *content, size_t size)
{
	size_t		i;

	change_endian(content, size);
	i = 0;
	while (i < size)
	{
		ft_memmove(vm->mem + ((position + i) % MEM_SIZE), content + i, 1);
		i++;
	}
	visu_update_vm(vm, position, content, size);
}

void		write_possess(t_vm *vm, uint32_t position, int champ, size_t size)
{
	size_t		i;

	i = 0;
	while (i < size)
	{
		vm->possess[(position + i) % MEM_SIZE] = champ;
		i++;
	}
}
