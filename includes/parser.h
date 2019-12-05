/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:32:22 by gtaja             #+#    #+#             */
/*   Updated: 2019/11/04 00:42:59 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "op.h"
# include "libft.h"
# include "lib.h"

# define BINARY_BUFF_SIZE	12
# define BINARY_ARRAY_CHUNK	12

# define PARSER_SUCCESS				0
# define PARSER_IGNORE				10

# define PARSER_NOT_LABEL			20

# define PARSER_CANT_OPEN_SOURCE	-1
# define PARSER_CANT_CREATE_BINARY	-2

# define PARSER_BAD_CMD				-11
# define PARSER_MULTIPLE_NAME		-12
# define PARSER_MULTIPLE_COMMENT	-13
# define PARSER_BAD_STRING			-14
# define PARSER_TOO_LONG_NAME		-15
# define PARSER_TOO_LONG_COMMENT	-16
# define PARSER_BAD_NUMBER			-17
# define PARSER_EMPTY_CODE			-18

# define PARSER_BAD_LABEL			-20
# define PARSER_BAD_INSTRUCTION		-21
# define PARSER_BAD_ARG_TYPE		-22
# define PARSER_BAD_ARG_VALUE		-23
# define PARSER_WRONG_ARGS_NUMBER	-24
# define PARSER_BAD_REGISTER		-25

# define PARSER_UNKNOW_LABEL		-30
# define PARSER_LABEL_REDEFINE		-31
# define PARSER_ENDS_WITHOUT_NL		-32

# define PARSER_WRONG_FILE			-40

typedef enum	e_parse_state
{
	HEADER,
	INSTRCUTIONS
}				t_parse_state;

typedef struct	s_binary
{
	unsigned char	**binary_array;
	size_t			current_buff_size;
	size_t			current_array_size;
	size_t			array_max_size;
	size_t			cursor;
}				t_binary;

typedef struct	s_label
{
	char		*name;
	size_t		address;
}				t_label;

typedef struct	s_waiting_label
{
	char		*name;
	size_t		cursor;
	size_t		address;
	size_t		size;
	int			line;
}				t_waiting_label;

typedef struct	s_parser
{
	t_parse_state	state;
	int				fd_source;
	int				fd_bin;
	char			*out_file;
	int				line;

	t_header		header;
	int				name_count;
	int				comment_count;

	t_op			*current_op;
	t_list			*labels;
	t_list			*waitings_labels;
	size_t			current_instruction_address;
	t_binary		binary;
}				t_parser;

/*
** BINARY
*/

void			write_byte_hex(unsigned char byte);
void			binary_init(t_binary *bin);
void			binary_write(t_binary *bin, void *content, size_t len);
void			binary_write_switch_endian(t_binary *bin, uint8_t *bytes,
	int size);
void			binary_write_null(t_binary *bin, int n);
void			binary_seek(t_binary *bin, int offset, int whence);
void			binary_export(t_binary *bin, int fd);
size_t			binary_size(t_binary *bin);
void			binary_show(t_binary *bin);
void			binary_free(t_binary *bin);

/*
** PARSER
*/

void			parser_start(char *source_file, char *out_file);
int				parser_main(t_parser *parser);
int				parser_search_string(t_parser *parser, char *str,
	char **result);
int				parser_header(t_parser *parser, char *line);
int				parser_instruction(t_parser *parser, char *line);
int				parser_find_args(t_parser *parser, char **line);
int				parser_manage_labels(t_parser *parser);
int				parser_export(t_parser *parser);
void			parser_log_error(t_parser *parser, int code);
void			parser_free(t_parser *parser);

void			skip_whitespace(char **str);
unsigned int	atoi_move(t_parser *parser, char **str);
t_arg_type		get_arg_type_asm(char **line);
size_t			get_arg_length(t_arg_type type, t_op *op);

/*
** DEBUG
*/

void			parser_debug_header(t_parser *parser);

#endif
