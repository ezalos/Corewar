/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_access.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 18:09:42 by ldevelle          #+#    #+#             */
/*   Updated: 2019/11/02 15:05:58 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void		write_registre(t_process *process, uint32_t reg, uint32_t arg)
{
	if (reg >= REG_NUMBER)
		return ;
	change_endian(&arg, REG_SIZE);
	ft_memmove(process->registre + (reg * REG_SIZE), &arg, REG_SIZE);
}

void		move_pc(t_process *process, uint32_t move, uint8_t two_bits)
{
	visu_update_pc(process->vm, process->pc, PC_DELETE);
	if (!two_bits)
		process->pc = pc_access(process->pc, move, NOT_PC_RESTRICT);
	else
		process->pc = pc_access_short(process->pc, (int16_t)move,
			NOT_PC_RESTRICT);
	visu_update_pc(process->vm, process->pc, PC_CREATE);
}

uint32_t	pc_access(uint32_t pc, int32_t add, uint8_t idx_mod)
{
	if (idx_mod == TRUE)
		pc = (int32_t)pc + (int32_t)(add % IDX_MOD);
	else
		pc = (int32_t)pc + (int32_t)add;
	pc = pc % MEM_SIZE;
	return (pc);
}

uint32_t	pc_access_short(uint32_t pc, int16_t add, uint8_t idx_mod)
{
	if (idx_mod == TRUE)
		pc = (int32_t)pc + (int16_t)(add % IDX_MOD);
	else
		pc = (int32_t)pc + (int16_t)add;
	pc = pc % MEM_SIZE;
	return (pc);
}
