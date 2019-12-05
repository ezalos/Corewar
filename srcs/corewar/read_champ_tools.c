/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champ_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 17:26:41 by ldevelle          #+#    #+#             */
/*   Updated: 2019/10/28 17:16:05 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"
#include "lib.h"

int					read_magic_nb(char *magic_numb)
{
	uint32_t		magic_num;
	int				ret;

	ret = FAILURE;
	magic_num = COREWAR_EXEC_MAGIC;
	if (COREWAR_EXEC_MAGIC == conv_2_uint32(magic_numb, 1))
		ret = SUCCESS;
	return (ret);
}

int32_t				read_size_champ(char *size_prog)
{
	uint32_t		size_champ;
	size_t			file_pos;

	file_pos = get_size_elmnt(size_prog, F_POS_SIZE);
	size_champ = (conv_2_uint32(size_prog + file_pos, 1));
	return (size_champ);
}

size_t				get_size_elmnt(char *file_str, int elmnt)
{
	size_t			pos_elmnt;

	pos_elmnt = 0;
	if (elmnt >= F_POS_MAGIC_NB)
		pos_elmnt = 0;
	if (elmnt >= F_POS_NAME)
		pos_elmnt += round_next_four(4);
	if (elmnt >= F_POS_SIZE)
		pos_elmnt += round_next_four(PROG_NAME_LENGTH + 1);
	if (elmnt >= F_POS_COMM)
		pos_elmnt += round_next_four(4);
	if (elmnt >= F_POS_CODE)
		pos_elmnt += round_next_four(COMMENT_LENGTH + 1);
	if (elmnt >= F_POS_END)
		pos_elmnt += read_size_champ(file_str);
	return (pos_elmnt);
}

int					vm_champ_start_position(int this_champ, int tt_of_champ)
{
	return ((this_champ - 1) * (MEM_SIZE / (tt_of_champ)));
}
