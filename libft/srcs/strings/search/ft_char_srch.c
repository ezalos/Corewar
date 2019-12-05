/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_srch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 13:39:11 by ldevelle          #+#    #+#             */
/*   Updated: 2019/01/21 14:10:20 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_char_srch(const char src, const char *dlt)
{
	while (*dlt)
	{
		if (src == *dlt)
			return (1);
		dlt++;
	}
	return (0);
}