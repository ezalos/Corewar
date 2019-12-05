/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_write.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 22:08:59 by gtaja             #+#    #+#             */
/*   Updated: 2019/11/01 15:20:16 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Verifie la taille du tableau et buffer puis alloue et copie si necessaire
*/

static void	ensure_buffer_memory(t_binary *bin)
{
	unsigned char	**new_array_buffer;
	int				i;

	if (bin->current_buff_size >= BINARY_BUFF_SIZE)
	{
		if (bin->current_array_size >= bin->array_max_size)
		{
			i = -1;
			new_array_buffer = ft_memalloc(
				(bin->array_max_size + BINARY_ARRAY_CHUNK)
				* sizeof(char*));
			while (++i < (int)bin->array_max_size)
				new_array_buffer[i] = bin->binary_array[i];
			ft_memdel((void**)&bin->binary_array);
			bin->binary_array = new_array_buffer;
			bin->array_max_size += BINARY_ARRAY_CHUNK;
		}
		bin->current_array_size += 1;
		bin->binary_array[bin->current_array_size - 1] =
			ft_memalloc(sizeof(char) * BINARY_BUFF_SIZE);
		bin->current_buff_size = 0;
	}
}

/*
**	Ecrit dans le binaire à la position du curseur
*/

void		binary_write(t_binary *bin, void *content, size_t len)
{
	size_t			i;
	unsigned char	*c_content;
	int				cur_array;
	int				cur_buff;

	c_content = (unsigned char*)content;
	cur_array = bin->cursor / BINARY_BUFF_SIZE;
	cur_buff = bin->cursor % BINARY_BUFF_SIZE;
	while (len > 0 && !(i = 0))
	{
		ensure_buffer_memory(bin);
		while (i < len && cur_buff < BINARY_BUFF_SIZE)
		{
			bin->binary_array[cur_array][cur_buff++] = c_content[i];
			bin->cursor += 1;
			if (cur_array == (int)(bin->current_array_size - 1)
				&& cur_buff > (int)bin->current_buff_size)
				bin->current_buff_size = cur_buff;
			i++;
		}
		c_content = c_content + i;
		len -= i;
		cur_array++;
		cur_buff = 0;
	}
}

/*
** Ecrit un uint32_t en BIG_ENDIAN
*/

void		binary_write_switch_endian(t_binary *bin, uint8_t *bytes, int size)
{
	uint8_t		*tab;

	tab = switch_endian(bytes, size);
	binary_write(bin, tab, size);
	ft_memdel((void**)&tab);
}

/*
** Ecrit des 0 dans les n prochains octet du binaire
*/

void		binary_write_null(t_binary *bin, int n)
{
	int		ref;

	ref = 0;
	while (--n >= 0)
		binary_write(bin, &ref, 1);
}
