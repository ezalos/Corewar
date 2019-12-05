/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_instruction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 16:53:02 by gtaja             #+#    #+#             */
/*   Updated: 2019/11/01 15:22:33 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Ajoute un label dans le parser
*/

static int	add_label(t_parser *parser, char *line, int len)
{
	t_list	*it;
	t_label	*tmp;
	t_label	*label;

	label = ft_memalloc(sizeof(t_label));
	label->name = ft_strndup(line, len);
	it = parser->labels;
	while (it != NULL)
	{
		tmp = (t_label*)(it->content);
		if (ft_strequ(tmp->name, label->name))
		{
			ft_memdel((void**)&label->name);
			ft_memdel((void**)&label);
			return (PARSER_LABEL_REDEFINE);
		}
		it = it->next;
	}
	label->address = parser->binary.cursor;
	ft_lstadd(&(parser->labels), ft_lstnew_ptr(label, sizeof(t_label)), -1);
	return (PARSER_SUCCESS);
}

/*
** Ajoute un label dans le parser si il existe et bouge
** le pointeur sur line dans ce cas
** Sinon return PARSER_NOT_LABEL
*/

static int	find_label(t_parser *parser, char **line)
{
	int	fct_res;
	int	i;

	i = 0;
	while (line[0][i] != LABEL_CHAR && line[0][i] != '\0')
	{
		if (ft_strchr(LABEL_CHARS, line[0][i]) == NULL)
			return (PARSER_NOT_LABEL);
		i++;
	}
	if (line[0][i] == '\0')
		return (PARSER_NOT_LABEL);
	if ((fct_res = add_label(parser, *line, i)) != PARSER_SUCCESS)
		return (fct_res);
	*line = *line + i + 1;
	skip_whitespace(line);
	return (PARSER_SUCCESS);
}

/*
** Compare l'instruction avec le debut de ligne
*/

static int	is_op(char *line, t_op *op)
{
	size_t	search_size;

	search_size = 0;
	while (line[search_size] != ' '
		&& line[search_size] != '\t' && line[search_size] != '\0')
		search_size++;
	if (line[search_size] == '\0')
		return (FALSE);
	if (search_size != ft_strlen(op->name))
		return (FALSE);
	else
		return (ft_strstartwith(line, op->name));
}

/*
** Trouve l'operation et la stoque dans *op
*/

static int	find_opcode(t_parser *parser, char **line)
{
	int	i;

	i = 0;
	if (line[0][0] == '\0')
		return (PARSER_IGNORE);
	while (g_op_tab[i].name != NULL)
	{
		if (is_op(*line, &(g_op_tab[i])))
		{
			parser->current_op = &(g_op_tab[i]);
			*line = *line + ft_strlen(g_op_tab[i].name);
			skip_whitespace(line);
			parser->current_instruction_address = parser->binary.cursor;
			binary_write(&(parser->binary), &(g_op_tab[i].opcode),
				sizeof(char));
			return (PARSER_SUCCESS);
		}
		i++;
	}
	return (PARSER_BAD_INSTRUCTION);
}

/*
** Parse une ligne et ecrit le binaire directement
*/

int			parser_instruction(t_parser *parser, char *line)
{
	int		is_lbl;
	int		fct_res;

	if ((is_lbl = find_label(parser, &line)) < 0)
		return (is_lbl);
	if ((fct_res = find_opcode(parser, &line)) != PARSER_SUCCESS)
	{
		return (is_lbl == PARSER_SUCCESS &&
			fct_res == PARSER_IGNORE ? is_lbl : fct_res);
	}
	if ((fct_res = parser_find_args(parser, &line)) != PARSER_SUCCESS)
		return (fct_res);
	return (PARSER_SUCCESS);
}
