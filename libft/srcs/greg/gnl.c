/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 18:06:54 by gtaja             #+#    #+#             */
/*   Updated: 2019/11/04 00:02:42 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*split_buffer(char *result, char *buffer, int len)
{
	char		*backslash;

	backslash = ft_strchr(result, '\n');
	if (backslash != NULL)
	{
		ft_strcpy(buffer, backslash + 1);
		backslash[1] = '\0';
	}
	else
		buffer[0] = '\0';
	if (len <= 0 && result[0] == '\0')
	{
		ft_memdel((void**)&result);
		return (NULL);
	}
	else
		return (result);
}

int			gnl(int fd, char **line)
{
	return (gnl_check_zero(fd, line, FALSE));
}

int			gnl_check_zero(int fd, char **line, int check_zero)
{
	static char	buffer[BUFF_SIZE + 1] = {0};
	char		*result;
	int			len;
	int			res_code;

	result = ft_strdup(buffer);
	len = 1;
	while (len > 0 && ft_strchr(result, '\n') == NULL)
	{
		len = read(fd, buffer, BUFF_SIZE);
		if (len <= 0)
			break ;
		if (check_zero && buffer[0] == 0)
		{
			ft_memdel((void**)&result);
			return (0);
		}
		buffer[len] = '\0';
		ft_strappend(&result, buffer);
	}
	res_code = len > 0 || result[0] != '\0';
	*line = split_buffer(result, buffer, len);
	return (res_code);
}
