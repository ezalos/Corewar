/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_ascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 20:29:22 by ldevelle          #+#    #+#             */
/*   Updated: 2019/11/01 14:57:02 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

int			visu_place_ascii(WINDOW *w_w, char *path, int row, int col)
{
	int		fd;
	char	*line;
	int		i;
	int		max_width;

	max_width = 0;
	i = 0;
	if ((fd = open(path, O_RDONLY)) > 0)
	{
		while (gnl(fd, &line) > 0)
		{
			if ((int)ft_strlen(line) > max_width)
				max_width = (int)ft_strlen(line);
			(w_w) ? wmove(w_w, row + i, col) : move(row + i, col);
			(w_w) ? wprintw(w_w, "%s", line) : printw("%s", line);
			i++;
			ft_memdel((void**)&line);
		}
		ft_memdel((void**)&line);
		close(fd);
		if (w_w)
			wrefresh(w_w);
		refresh();
	}
	return ((i * 1000) + max_width);
}

void		visu_wesh_wesh(t_vm *vm, int on_off)
{
	if (on_off)
	{
		werase(vm->visu.w_proc);
		wattron(vm->visu.w_proc, COLOR_PAIR(GD_COLOR));
		visu_place_ascii(vm->visu.w_proc, "./ressources/fight.ascii", 1, 3);
		wattroff(vm->visu.w_proc, COLOR_PAIR(GD_COLOR));
	}
	else
	{
		werase(vm->visu.w_proc);
		wborder(vm->visu.w_proc, '|', '|', '-', '-', '+', '+', '+', '+');
	}
}

void		visu_update_head(t_vm *vm)
{
	visu_refresh(vm, V_HEAD | V_V);
	attron(COLOR_PAIR(RD_COLOR));
	visu_place_ascii(NULL, "./ressources/core.ascii",
		1, (SATYR_SPACE + W_HEAD - 86) / 2);
	attroff(COLOR_PAIR(RD_COLOR));
	visu_refresh(vm, V_HEAD | V_V);
	if (SATYR_SPACE)
	{
		attron(COLOR_PAIR(BW_COLOR));
		visu_place_ascii(NULL, "./ressources/satyr.ascii",
			H_HEAD + H_VM - 38, 2);
		attroff(COLOR_PAIR(BW_COLOR));
		refresh();
	}
	attron(COLOR_PAIR(GD_COLOR));
	visu_place_ascii(NULL, "./ressources/trophy.ascii",
		1, SATYR_SPACE + W_VM + ((W_PANEL - 28) / 2));
	attroff(COLOR_PAIR(GD_COLOR));
	refresh();
}
