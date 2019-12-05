/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 20:45:34 by gtaja             #+#    #+#             */
/*   Updated: 2019/11/01 15:18:20 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

/*
** Prepare un objet t_binary a sont utilisation
** Dans l'ideal créez une variable t_binary et passez y l'adresse
*/

void	binary_init(t_binary *bin)
{
	ft_bzero(bin, sizeof(t_binary));
	bin->binary_array = ft_memalloc(sizeof(char*) * BINARY_ARRAY_CHUNK);
	bin->binary_array[0] = ft_memalloc(sizeof(char) * BINARY_BUFF_SIZE);
	bin->current_array_size = 1;
	bin->array_max_size = BINARY_ARRAY_CHUNK;
}

/*
** Retourne la taille en octet du binaire
*/

size_t	binary_size(t_binary *bin)
{
	size_t	size;

	size = bin->current_array_size * BINARY_BUFF_SIZE;
	size -= BINARY_BUFF_SIZE - bin->current_buff_size;
	return (size);
}

/*
** Free le contenu d'un objet t_binary,
** ATTENTION : vous devez vous meme free l'objet
**   en lui meme si vous l'avez malloc
*/

void	binary_free(t_binary *bin)
{
	size_t	i;

	i = 0;
	while (i < bin->current_array_size)
	{
		ft_memdel((void**)&bin->binary_array[i]);
		i++;
	}
	ft_memdel((void**)&bin->binary_array);
}
