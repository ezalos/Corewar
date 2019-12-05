/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endian.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 15:59:27 by gtaja             #+#    #+#             */
/*   Updated: 2019/10/31 10:46:07 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "libft.h"

/*
** Prend un tableau d'octet en LITTLE ENDIAN et le retourne en BIG ENDIAN
*/

uint8_t	*switch_endian(uint8_t *val, int size)
{
	uint8_t	*out;
	int		i;

	out = ft_memalloc(sizeof(uint8_t) * size);
	i = 0;
	while (i < size)
	{
		out[i] = val[size - 1 - i];
		i++;
	}
	return (out);
}

/*
** Ecrit un uint32_t dans le file descriptor en BIG ENDIAN
** (Le mac est en LITTLE ENDIAN)
*/

void	write_switch_endian(int fd, uint32_t value)
{
	uint8_t	*reverse;

	reverse = switch_endian((uint8_t*)(&value), sizeof(uint32_t));
	write(fd, reverse, sizeof(uint32_t));
	ft_memdel((void**)&reverse);
}
