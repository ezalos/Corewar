/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doigts_dans_le_cul_de_la_norminette.h              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 16:19:05 by gtaja             #+#    #+#             */
/*   Updated: 2019/11/01 16:34:47 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOIGTS_DANS_LE_CUL_DE_LA_NORMINETTE_H
# define DOIGTS_DANS_LE_CUL_DE_LA_NORMINETTE_H

typedef struct	s_visu_str_wrap
{
	char	*str;
	int		col;
	int		row;
	char	path[24];
	int		len;
	int		width_letter;
	int		r_supp;
	int		c_supp;
	int		i;
}				t_visu_str_wrap;

typedef struct	s_visu_intro_wrap
{
	char	*number;
	int		col;
	int		row;
	int		tmp;
	int		i;
}				t_visu_intro_wrap;

#endif
