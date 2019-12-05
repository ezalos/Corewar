/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 17:26:41 by ldevelle          #+#    #+#             */
/*   Updated: 2019/11/03 19:45:39 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"
#include "libft.h"

static uint8_t		isread_file_sizes_valid(char *file_str, size_t size)
{
	int		ret;

	ret = FAILURE;
	if (size >= get_size_elmnt(file_str, F_POS_CODE))
		if (size <= get_size_elmnt(file_str, F_POS_CODE) + CHAMP_MAX_SIZE)
			if (file_str && read_magic_nb(file_str) == SUCCESS)
				if (size == get_size_elmnt(file_str, F_POS_END))
					ret = SUCCESS;
	return (ret);
}

static void			champ_write_in_structs(t_vm *vm, int write_pos,
	t_champion *champ, char *file_str)
{
	size_t			file_pos;

	file_pos = get_size_elmnt(file_str, F_POS_NAME);
	ft_memmove(champ->name, file_str + file_pos, PROG_NAME_LENGTH);
	file_pos = get_size_elmnt(file_str, F_POS_COMM);
	ft_memmove(champ->comment, file_str + file_pos, COMMENT_LENGTH);
	file_pos = get_size_elmnt(file_str, F_POS_CODE);
	ft_memmove(vm->mem + (write_pos % MEM_SIZE), file_str + file_pos,
		get_size_elmnt(file_str, F_POS_END) - file_pos);
	write_possess(vm, write_pos, champ->number,
		get_size_elmnt(file_str, F_POS_END) - file_pos);
	visu_update_vm(vm, write_pos, vm->mem + (write_pos % MEM_SIZE),
		get_size_elmnt(file_str, F_POS_END) - file_pos);
}

void				read_champ_quit_error(char *str1, char *str2)
{
	ft_putstr_fd(str1, 2);
	ft_putendl_fd(str2, 2);
	exit(EXIT_FAILURE);
}

void				read_champ_add_process(t_vm *vm, t_champion *champ,
											int champ_nb, int ret)
{
	if (ret == FAILURE)
		read_champ_quit_error("Cannot open file: ",
			vm->options.path_champ[champ_nb]);
	else
	{
		champ->exist = 1;
		add_process_to_vm(vm, create_process(champ,
		vm_champ_start_position(champ_nb + 1,
			vm->options.nb_champ)));
	}
}

int					read_cor_champ(t_vm *vm, t_champion *champ, int champ_nb)
{
	char	*file_str;
	int		size;
	int		ret;
	int		fd;

	ret = FAILURE;
	if ((fd = open(vm->options.path_champ[champ_nb], O_RDONLY)) > 0)
	{
		champ->number = vm->options.number_champ[champ_nb];
		file_str = ft_read_file(fd, &size);
		close(fd);
		if (file_str && isread_file_sizes_valid(file_str, size) == SUCCESS)
		{
			champ_write_in_structs(vm, vm_champ_start_position(champ_nb + 1,
				vm->options.nb_champ), champ, file_str);
			champ->alive = TRUE;
			ret = SUCCESS;
		}
		else
			read_champ_quit_error("Invalid champ: ",
			vm->options.path_champ[champ_nb]);
		ft_strdel(&file_str);
	}
	read_champ_add_process(vm, champ, champ_nb, ret);
	return (ret);
}
