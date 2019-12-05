/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 16:29:37 by gtaja             #+#    #+#             */
/*   Updated: 2019/10/22 16:11:20 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include <inttypes.h>
# include <string.h>

uint8_t	*switch_endian(uint8_t *val, int size);
void	write_switch_endian(int fd, uint32_t value);
size_t	round_next_four(size_t size);

#endif
