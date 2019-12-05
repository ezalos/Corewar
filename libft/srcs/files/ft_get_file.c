/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 15:46:14 by ldevelle          #+#    #+#             */
/*   Updated: 2019/10/22 09:27:57 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_get_file(char *path, char **file)
{
	int			fd;
	int			size;

	if (!file || !(fd = open(path, O_RDONLY)))
		return (-1);
	*file = ft_read_file(fd, &size);
	close(fd);
	return (size);
}
