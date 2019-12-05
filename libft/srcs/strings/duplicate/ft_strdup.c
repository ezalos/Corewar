/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:11:48 by ldevelle          #+#    #+#             */
/*   Updated: 2019/10/01 15:59:35 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		i;
	int		size;

	size = ft_strlen(src);
	if (!(dest = (char*)P_MALLOC(sizeof(char) * (size + 1))))
		return (NULL);
	dest[size] = '\0';
	i = -1;
	while (++i < size)
		dest[i] = src[i];
	return (dest);
}
