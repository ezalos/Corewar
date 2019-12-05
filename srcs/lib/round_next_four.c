/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   round_next_four.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 16:10:37 by gtaja             #+#    #+#             */
/*   Updated: 2019/10/22 16:11:49 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

/*
** Arrondi au multiple de 4 supérieur
** C'est utile pour connaitre la taille reel en memoire
** d'un char[] (oui, c'est arrondit au multiple de 4 superieur)
*/

size_t	round_next_four(size_t size)
{
	if (size % 4 == 0)
		return (size);
	return (size + 4 - size % 4);
}
