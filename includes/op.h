/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaja <gtaja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2019/11/01 15:12:27 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
*/

#ifndef OP_H
# define OP_H

# define IND_SIZE				2
# define REG_SIZE				4
# define REGSTR_SIZE			1
# define DIR_SIZE				REG_SIZE
# define DIR_2B_SIZE			2

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define PC_RESTRICT			1
# define NOT_PC_RESTRICT		0

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

# define FIRST_ARG				192
# define SECOND_ARG				48
# define THIRD_ARG				12
# define FOURTH_ARG				3

/*
** --
*/

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

# include "arena.h"

typedef unsigned char			t_arg_type;
typedef unsigned int			t_uint;

typedef struct					s_header
{
	t_uint						magic;
	char						prog_name[PROG_NAME_LENGTH + 1];
	t_uint						prog_size;
	char						comment[COMMENT_LENGTH + 1];
}								t_header;

#endif
