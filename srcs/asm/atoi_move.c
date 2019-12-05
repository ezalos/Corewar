/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 22:21:26 by gtaja             #+#    #+#             */
/*   Updated: 2019/11/03 23:59:14 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int		ensure_error(t_parser *parser, long res, int error)
{
	if (error)
	{
		parser_log_error(parser, PARSER_BAD_NUMBER);
		exit(EXIT_FAILURE);
	}
	return (res);
}

static void		init_var(int *i, int *sign, long *res, int *error)
{
	*i = 0;
	*sign = 1;
	*res = 0;
	*error = 1;
}

static int		check_overflow(long *res, int sign, int *stop_count)
{
	if (*res >= UINT_MAX)
	{
		*res = sign > 0 ? UINT_MAX : 0;
		*stop_count = TRUE;
	}
	return (TRUE);
}

/*
** Fais un atoi et bouge *str à la fin du nombre dans la chaine
*/

unsigned int	atoi_move(t_parser *parser, char **str)
{
	int		i;
	int		sign;
	long	res;
	int		error;
	int		stop_count;

	init_var(&i, &sign, &res, &error);
	if ((stop_count = FALSE) || str == NULL || *str == NULL)
		return (0);
	while (((**str >= 8 && **str <= 13) || **str == ' ') && **str)
		*str = *str + 1;
	if (**str == '-' || **str == '+')
	{
		sign = **str == '-' ? -1 : 1;
		*str = *str + 1;
	}
	while (**str >= '0' && **str <= '9')
	{
		error = 0;
		check_overflow(&res, sign, &stop_count);
		if (!stop_count)
			res = res * 10 + **str - 48;
		*str = *str + 1;
	}
	return (ensure_error(parser, res * (long)sign, error));
}
