/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 23:03:26 by gtaja             #+#    #+#             */
/*   Updated: 2019/09/30 23:19:00 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Ecrit le binaire dans le fd
*/

void	binary_export(t_binary *bin, int fd)
{
	size_t	i;

	i = 0;
	while (i < bin->current_array_size - 1)
	{
		write(fd, bin->binary_array[i], BINARY_BUFF_SIZE);
		i++;
	}
	write(fd, bin->binary_array[i], bin->current_buff_size);
}
