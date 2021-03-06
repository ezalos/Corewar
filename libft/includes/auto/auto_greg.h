/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_greg.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 07:40:18 by gtaja             #+#    #+#             */
/*   Updated: 2019/11/03 17:45:24 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTO_GREG_H
# define AUTO_GREG_H

int			ft_strappend(char **base, char *more);
int			ft_strendswith(char *str, char *ends);
char		*ft_strndup(char *str, size_t n);
int			ft_strstartwith(char *str, char *start);
char		*ft_strtrim_free(char *str);
int			gnl(int fd, char **line);
int			gnl_check_zero(int fd, char **line, int check_zero);

#endif
