/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 17:21:01 by ldevelle          #+#    #+#             */
/*   Updated: 2019/11/03 07:51:22 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

t_process			*create_empty_process(void)
{
	t_process		*out;

	out = ft_memalloc(sizeof(t_process));
	out->pc = -1;
	out->timer = -1;
	out->carry = 0;
	return (out);
}

t_process			*create_process(t_champion *owner, int pc)
{
	t_process		*out;
	unsigned int	process_num;

	out = create_empty_process();
	out->owner = owner;
	out->pc = pc;
	process_num = 0;
	process_num -= owner->number;
	ft_memcpy(out->registre, &process_num, REG_SIZE);
	change_endian(out->registre, 4);
	return (out);
}

t_process			*copy_process(t_process *src)
{
	t_process		*out;

	out = create_empty_process();
	out->pc = src->pc;
	out->carry = src->carry;
	out->last_live = src->last_live;
	out->owner = src->owner;
	out->lives_since_check = src->lives_since_check;
	ft_memcpy(out->registre, src->registre, REG_NUMBER * REG_SIZE);
	return (out);
}

void				add_process_to_vm(t_vm *vm, t_process *process)
{
	static int		fact;

	if (vm == NULL || process == NULL)
		ft_printf("NULL PUSH FRONT\n");
	process->vm = vm;
	process->next = vm->process_start;
	vm->process_start = process;
	visu_update_pc(vm, process->pc, PC_CREATE);
	vm->tt_pc++;
	process->num = ++fact;
}

t_process			*rm_process_to_vm(t_process *process, t_process *prev)
{
	t_process	*no_segfault;
	t_process	*del;

	del = process;
	if (prev == NULL)
	{
		process->vm->process_start = del->next;
		no_segfault = del->next;
		del->vm->tt_pc--;
		visu_update_pc(del->vm, del->pc, PC_DELETE);
		ft_memdel((void**)&del);
		return (no_segfault);
	}
	prev->next = del->next;
	del->vm->tt_pc--;
	visu_update_pc(del->vm, del->pc, PC_DELETE);
	ft_memdel((void**)&del);
	return (prev->next);
}
