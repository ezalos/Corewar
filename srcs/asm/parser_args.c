/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 13:33:53 by gtaja             #+#    #+#             */
/*   Updated: 2019/11/03 18:54:23 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Ajoute un label dans la liste des labels en attente d'etre evalué
*/

static t_waiting_label	*create_waiting_label(t_parser *parser,
	char **line, size_t arg_size)
{
	t_waiting_label	*wl;
	size_t			i;
	size_t			name_size;

	wl = ft_memalloc(sizeof(t_waiting_label));
	wl->cursor = parser->binary.cursor;
	wl->address = parser->current_instruction_address;
	wl->size = arg_size;
	wl->line = parser->line;
	name_size = 0;
	while (line[0][name_size] != '\0'
		&& ft_strchr(LABEL_CHARS, line[0][name_size]) != NULL)
		name_size++;
	wl->name = ft_memalloc((name_size + 1) * sizeof(char));
	wl->name[name_size] = '\0';
	i = 0;
	while (i < name_size)
	{
		wl->name[i] = **line;
		*line += 1;
		i++;
	}
	return (wl);
}

/*
** Verifie la validité des registres
*/

static int				ensure_arg(uint32_t value, t_arg_type type)
{
	if (type == T_REG)
	{
		if (value > REG_NUMBER)
			return (PARSER_BAD_REGISTER);
	}
	return (PARSER_SUCCESS);
}

/*
** On lit et save l'argument
** Ou on le met en attente si c'est un label
** (le label est peu etre defini apres)
*/

static int				find_arg(t_parser *parser, char **line, int n,
	t_arg_type *found_type)
{
	uint32_t	value;
	size_t		arg_size;

	*found_type = get_arg_type_asm(line);
	arg_size = get_arg_length(*found_type, parser->current_op);
	if (!(parser->current_op->args_type[n] & (*found_type)))
		return (PARSER_BAD_ARG_TYPE);
	if (line[0][0] == LABEL_CHAR)
	{
		*line = *line + 1;
		ft_lstadd(&(parser->waitings_labels),
			ft_lstnew_ptr(
				create_waiting_label(parser, line, arg_size),
				sizeof(t_waiting_label)), -1);
		binary_write_null(&(parser->binary), arg_size);
		return (PARSER_SUCCESS);
	}
	else
	{
		value = (uint32_t)atoi_move(parser, line);
		binary_write_switch_endian(&(parser->binary),
			(uint8_t*)(&value), arg_size);
		return (ensure_arg(value, *found_type));
	}
}

/*
** Ecrit l'octet de codage des parametres (OCP)
** La fonction reviens en arriere dans le binaire puis avance au point initial
** Attention il faut verifier avant que l'instruction nécessite un OCP
*/

static void				write_ocp(t_binary *bin, t_op *op, t_arg_type types[3])
{
	char	result;
	char	code;
	int		i;
	int		seek;

	result = 0;
	i = -1;
	seek = 1;
	while (++i < (int)op->nb_args)
		seek += get_arg_length(types[i], op);
	binary_seek(bin, -seek, SEEK_CUR);
	i = -1;
	while (++i < (int)op->nb_args)
	{
		code = (types[i] == T_REG) + 2 * (types[i] == T_DIR) + 3
			* (types[i] == T_IND);
		result = (result | code) << 2;
	}
	result <<= 2 * (3 - i);
	binary_write(bin, &result, sizeof(char));
	binary_seek(bin, seek - 1, SEEK_CUR);
}

/*
** Recupere les arguments en fonctions de l'op
*/

int						parser_find_args(t_parser *parser, char **line)
{
	t_uint		i;
	int			fct_res;
	t_arg_type	types[3];

	i = 0;
	if (parser->current_op->need_ocp)
		binary_write_null(&(parser->binary), 1);
	while (i < parser->current_op->nb_args)
	{
		skip_whitespace(line);
		if ((fct_res = find_arg(parser, line, i, &(types[i])))
			!= PARSER_SUCCESS)
			return (fct_res);
		skip_whitespace(line);
		if ((i == parser->current_op->nb_args - 1 && **line != '\0') ||
			(i < parser->current_op->nb_args - 1 && **line != SEPARATOR_CHAR))
			return (PARSER_WRONG_ARGS_NUMBER);
		*line = *line + 1;
		i++;
	}
	if (parser->current_op->need_ocp)
		write_ocp(&(parser->binary), parser->current_op, types);
	return (PARSER_SUCCESS);
}
