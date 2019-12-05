/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 16:36:48 by gtaja             #+#    #+#             */
/*   Updated: 2019/11/03 17:49:37 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Gere l'initialisation du parsing et le lance
** Retourne PARSING_SUCCESS ou le code d'erreur
*/

static int	parser_wrapper(t_parser *parser, char *source_file, char *out_file)
{
	int			fct_res;

	parser->state = HEADER;
	parser->header.magic = COREWAR_EXEC_MAGIC;
	binary_init(&(parser->binary));
	if ((parser->fd_source = open(source_file, O_RDONLY)) < 0)
		return (PARSER_CANT_OPEN_SOURCE);
	parser->out_file = out_file;
	if ((fct_res = parser_main(parser)) != PARSER_SUCCESS)
		return (fct_res);
	close(parser->fd_bin);
	close(parser->fd_source);
	return (parser->state == INSTRCUTIONS ? PARSER_SUCCESS : PARSER_WRONG_FILE);
}

/*
** Lance l'initialisation et recupere le resultat
** Affiche l'erreur si besoin
*/

void		parser_start(char *source_file, char *out_file)
{
	t_parser	parser;
	int			res;

	ft_bzero(&parser, sizeof(t_parser));
	if ((res = parser_wrapper(&parser, source_file, out_file))
		!= PARSER_SUCCESS)
		parser_log_error(&parser, res);
	else
	{
		ft_putstr("Writing output program to ");
		ft_putendl(out_file);
	}
	parser_free(&parser);
}
