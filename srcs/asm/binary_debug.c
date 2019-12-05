/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 21:59:14 by gtaja             #+#    #+#             */
/*   Updated: 2019/10/07 16:28:18 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Affiche un octet en hexa dans la console
*/

void	write_byte_hex(unsigned char byte)
{
	char	base[17];

	ft_strcpy(base, "0123456789ABCDEF");
	write(1, base + (byte / 16), 1);
	write(1, base + (byte % 16), 1);
}

/*
** Affiche le binaire en hexa
*/

void	binary_show(t_binary *bin)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < bin->current_array_size)
	{
		j = 0;
		while (j < BINARY_BUFF_SIZE)
		{
			if (i == bin->current_array_size - 1 && j >= bin->current_buff_size)
				break ;
			write_byte_hex(bin->binary_array[i][j]);
			write(1, " ", 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}
