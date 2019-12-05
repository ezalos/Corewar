/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_seek.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 13:41:25 by gtaja             #+#    #+#             */
/*   Updated: 2019/10/08 13:41:36 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Permet de deplacer le curseur de offset octet :
** - Depuis le debut du binaire avec				whence == SEEK_SET
** - Depuis la position courante du curseur avec	whence == SEEK_CUR
** - Depuis la fin du binaire avec					whence == SEEK_END
*/

void		binary_seek(t_binary *bin, int offset, int whence)
{
	if (whence == SEEK_SET)
		bin->cursor = offset;
	else if (whence == SEEK_CUR)
		bin->cursor += offset;
	else if (whence == SEEK_END)
		bin->cursor = binary_size(bin) + offset;
}
