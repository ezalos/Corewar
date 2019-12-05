/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 22:08:15 by ldevelle          #+#    #+#             */
/*   Updated: 2019/11/02 16:20:56 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void		fast_terminal(float time, int size, int on_off)
{
	static struct termios	old = {0};

	if (on_off)
	{
		if (tcgetattr(0, &old) < 0)
			perror("tcsetattr()");
		old.c_lflag &= ~ICANON;
		old.c_lflag &= ~ECHO;
		old.c_cc[VMIN] = size;
		old.c_cc[VTIME] = time;
		if (tcsetattr(0, TCSANOW, &old) < 0)
			perror("tcsetattr ICANON");
	}
	else
	{
		old.c_lflag |= ICANON;
		old.c_lflag |= ECHO;
		if (tcsetattr(0, TCSADRAIN, &old) < 0)
			perror("tcsetattr ~ICANON");
	}
}

void		check_char(t_vm *vm, char line)
{
	if (line == ' ')
		vm->visu.pause = !vm->visu.pause;
	if (line == '-' && vm->visu.speed)
		vm->visu.speed = vm->visu.speed * 2;
	if (line == '-' && vm->visu.speed <= 0.1)
		vm->visu.speed = 0.5;
	if (line == '+' && vm->visu.speed > 0)
		vm->visu.speed /= 2;
	if (line == '*' && vm->visu.speed > 0)
		vm->visu.speed = 0;
	if (line == '1')
		vm->visu.update_type = UPDATE_PC;
	if (line == '2')
		vm->visu.update_type = UPDATE_CYCLE;
	if (line == '3')
		vm->visu.update_type = UPDATE_FUNC;
	if (line == '=')
	{
		vm->visu.proc = !vm->visu.proc;
		if (vm->visu.proc == 0)
			vm->visu.speed = 0;
		visu_wesh_wesh(vm, !vm->visu.proc);
	}
	vm->cycle > 1 ? visu_update_panel(vm) : 0;
	visu_refresh(vm, V_PANEL | V_V);
}

void		user_interact(t_vm *vm)
{
	char					*line;
	int						i;

	line = NULL;
	if (vm->visu.speed < 1)
	{
		fast_terminal(vm->visu.speed / 4, 0, 1);
		gnl(0, &line);
		if (line)
			check_char(vm, line[0]);
		ft_strdel(&line);
		fast_terminal(0, 0, 0);
	}
	else if ((i = -1))
	{
		fast_terminal(0.25, 0, 1);
		while (++i < (int)vm->visu.speed)
		{
			gnl(0, &line);
			if (line)
				check_char(vm, line[0]);
			ft_strdel(&line);
		}
		fast_terminal(0, 0, 0);
	}
}

void		control_speed(t_vm *vm)
{
	char	*line;
	int		i;

	line = NULL;
	if (vm->visu.visu)
	{
		i = -1;
		if (vm->visu.pause)
		{
			noecho();
			cbreak();
			check_char(vm, getch());
		}
		else
			user_interact(vm);
	}
}

void		call_visu(t_vm *vm, t_process *process, int type)
{
	if (vm->visu.visu)
	{
		(void)wait;
		if (process == NULL)
		{
			visu_update_panel(vm);
			if (type == UPDATE_CYCLE)
				visu_refresh(vm, V_VM | V_V);
		}
		else if (vm->visu.proc)
		{
			visu_update_process(process);
			if ((type == 0 && UPDATE_PC == vm->visu.update_type)
			|| (type == vm->visu.update_type
			&& UPDATE_PC != vm->visu.update_type))
				visu_refresh(vm, V_PROC | V_V);
		}
		if (0 == type || vm->visu.pause)
			visu_refresh(vm, V_VM | V_V);
		if ((type == 0 && UPDATE_PC == vm->visu.update_type)
		|| (type == vm->visu.update_type && UPDATE_PC != vm->visu.update_type))
			control_speed(vm);
		if (type >= vm->visu.update_type)
			visu_refresh(vm, V_V);
	}
}
