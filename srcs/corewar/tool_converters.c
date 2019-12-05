/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_converters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 17:18:13 by ldevelle          #+#    #+#             */
/*   Updated: 2019/11/01 16:25:11 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void			change_endian(void *big_endian, int size)
{
	int			tmp;
	int			i;
	int			n;

	i = 0;
	n = size - 1;
	while (i < n)
	{
		tmp = ((char*)big_endian)[i];
		((char*)big_endian)[i] = ((char*)big_endian)[n];
		((char*)big_endian)[n] = tmp;
		i++;
		n--;
	}
}

uint32_t		conv_2_uint32(char *size_prog, int edian_conv)
{
	uint32_t	size_champ;

	size_champ = 0;
	ft_memmove(&size_champ, size_prog, 4);
	if (edian_conv)
		change_endian(&size_champ, 4);
	return (size_champ);
}

void			put_nbr_hex(uint8_t nb, char *base)
{
	if (nb > 15)
		put_nbr_hex(nb / 16, base);
	ft_putchar(base[nb % 16]);
}
