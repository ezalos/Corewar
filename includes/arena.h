/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:57:29 by ldevelle          #+#    #+#             */
/*   Updated: 2019/11/04 01:31:21 by gtaja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_H
# define ARENA_H

# define DUMP_CHAR_BY_LINE	32

# define FUNCTION_SIZE	1
# define ARG_DEF_SIZE	1
# define MAX_ARG_SIZE	(IND_SIZE < REG_SIZE ? REG_SIZE : IND_SIZE)

# define F_POS_MAGIC_NB	0
# define F_POS_NAME		1
# define F_POS_SIZE		2
# define F_POS_COMM		3
# define F_POS_CODE		4
# define F_POS_END		5
# define CRASH			2

# define SPEED_INIT		262144 / 2

# define UPDATE_PC		1
# define UPDATE_CYCLE	2
# define UPDATE_FUNC	3

# define PC_DELETE		1
# define PC_CREATE		2
# define PC_ACTIF		3

# define V_VM			1
# define V_PANEL		2
# define V_HEAD			4
# define V_PROC			8
# define V_V			16

# define V_ALL			V_VM | V_PANEL | V_HEAD | V_PROC | V_V

# define H_VM			64 + (2 * UP_SPACE)
# define W_VM			(64 * 3) + 1 + (2 * LEFT_SPACE)

# define H_PANEL		H_VM - (H_PROC)
# define W_PANEL		80 + (2 * LEFT_SPACE)

# define H_HEAD			10 + (2 * UP_SPACE)
# define W_HEAD			W_VM + W_PANEL + (2 * LEFT_SPACE)

# define H_PROC			22 + (2 * UP_SPACE)
# define W_PROC			W_PANEL

# define SATYR_SPACE	42

# define UP_SPACE		1
# define LEFT_SPACE		2

# define P1_COLOR		1
# define P2_COLOR		2
# define P3_COLOR		3
# define P4_COLOR		4
# define NP_COLOR		5
# define BK_COLOR		6
# define PC_TMP_COLOR	7
# define AC_COLOR		8
# define WH_COLOR		9
# define RD_COLOR		10
# define BW_COLOR		11
# define GD_COLOR		12

# define WAIT_POS		454452415

# include <ncurses.h>
# include <inttypes.h>
# include "op.h"
# include "libft.h"
# include <termios.h>

typedef unsigned char	t_arg_type;
typedef unsigned int	t_uint;

typedef struct			s_champion {
	char				name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH + 1];

	int					exist;
	int					number;
	unsigned int		last_live_cycle;
	unsigned int		lives_since_check;

	int					alive;
}						t_champion;

typedef struct			s_args {
	int32_t				dir[3];
	int16_t				deu[3];
	uint32_t			idx[3];
	int8_t				use[3];
	int32_t				raw[3];
}						t_args;

typedef struct			s_process {
	uint8_t				registre[REG_NUMBER * REG_SIZE];
	uint8_t				bytecode[FUNCTION_SIZE + ARG_DEF_SIZE +\
						(MAX_ARG_SIZE * MAX_ARGS_NUMBER)];

	uint32_t			pc;
	ssize_t				timer;
	int					last_live;
	ssize_t				punition;
	uint8_t				carry;

	uint32_t			num;
	uint32_t			next_func;
	uint32_t			ocp;
	unsigned int		lives_since_check;
	t_champion			*owner;
	t_args				args;
	struct s_process	*next;
	struct s_vm			*vm;
}						t_process;

typedef struct			s_options {
	int					dump_cycles;
	int					nb_champ;
	int					visu;
	int					visu_break;
	int					verbose;
	int					mute;
	int					number_champ[MAX_PLAYERS];
	char				*path_champ[MAX_PLAYERS];
	int					available[MAX_PLAYERS];
}						t_options;

typedef struct			s_visu {
	int					visu;
	WINDOW				*w_vm;
	WINDOW				*w_head;
	WINDOW				*w_panel;
	WINDOW				*w_proc;
	float				speed;
	int					pause;
	int					color;
	int					proc;
	int					update_all_pc;
	int					update_type;
}						t_visu;

typedef int				(t_fct)(struct s_vm*, t_process*, t_args*);

typedef struct			s_op
{
	char				*name;
	t_uint				nb_args;
	t_arg_type			args_type[3];
	char				opcode;
	t_uint				nb_cycle;
	char				*description;
	t_uint				need_ocp;
	t_uint				is_direct_two_bytes;
}						t_op;

extern	t_op			g_op_tab[17];

typedef struct			s_vm {
	uint8_t				mem[MEM_SIZE];
	uint8_t				possess[MEM_SIZE];

	unsigned int		total_live_since_check;
	unsigned long		cycle;
	int					cycle_to_die;
	unsigned int		max_checks;
	t_champion			*last_alive_champ;

	t_process			*process_start;
	t_op				g_op_tab[17];
	t_champion			champions[MAX_PLAYERS];

	t_visu				visu;
	int					tt_pc;
	int					current_p;
	int					current_cycle;

	t_options			options;
	t_fct				*fct[17];
}						t_vm;

/*
******************************************************************************
**																			**
**								----------									**
**								PROTOTYPES									**
**								----------									**
**																			**
******************************************************************************
*/

/*
**  TO DO
*/
uint8_t					excecute(uint8_t *bytecode, t_vm *vm,
					t_process *process);

/*
**************
**   ARGS	**
**************
*/
int						check_ocp(unsigned char opcode, unsigned char arg_byte);
t_arg_type				get_arg_type_ocp(unsigned char arg_byte,
						t_uint arg_number);
uint8_t					get_arg_type(t_vm *vm, t_process *process,
						uint8_t arg_number);
uint32_t				get_arg_size(t_vm *vm, t_process *process,
						uint8_t arg_number);
uint32_t				get_arg_position(t_vm *vm, t_process *process,
						uint8_t arg_number);
int32_t					return_arg(t_vm *vm, t_process *process,
						uint8_t arg_number);
int8_t					load_args_in_struct(t_vm *vm, t_process *process);

/*
**************
**  INIT 	**
**************
*/
int						init(t_vm *vm, int ac, char **av);
int						init_arg_management(t_options *options, int ac,
						char **av);
void					reset_use(t_args *args);
void					init_visu(t_vm *vm);
int						usage_corewar(void);

/*
**************
**   READ	**
**************
*/
int						read_cor_champ(t_vm *vm, t_champion *champ,
						int champ_nb);
int						vm_champ_start_position(int this_champ,
						int tt_of_champ);
size_t					get_size_elmnt(char *file_str, int elmnt);
int						read_magic_nb(char *magic_numb);
int32_t					read_size_champ(char *size_prog);
size_t					get_size_elmnt(char *file_str, int elmnt);

/*
**************
**   TOOLS	**
**************
*/
void					change_endian(void *big_endian, int size);
uint32_t				conv_2_uint32(char *size_prog, int edian_conv);
void					put_nbr_hex(uint8_t nb, char *base);

/*
**************
**  PROCESS	**
**************
*/
t_process				*create_process(t_champion *owner, int pc);
t_process				*copy_process(t_process *src);
void					add_process_to_vm(t_vm *vm, t_process *process);
int						process_cycle(t_vm *vm);
t_process				*rm_process_to_vm(t_process *process, t_process *prev);
void					free_all_processes(t_vm *vm);

/*
**************
**   VM		**
**************
*/
uint32_t				add_pc_after_exec(t_args *args, t_process *process);
int						vm_cycle(t_vm *vm);
void					read_vm(t_vm *vm, uint32_t position, void *dest,
						uint32_t size);
uint32_t				read_vm_int(t_vm *vm, uint32_t position);
void					write_vm(t_vm *vm, uint32_t positon, void *content,
						size_t size);
void					write_registre(t_process *process, uint32_t reg,
						uint32_t arg);
uint32_t				pc_access(uint32_t pc, int32_t add, uint8_t idx_mod);
uint32_t				pc_access_short(uint32_t pc, int16_t add,
						uint8_t idx_mod);
void					move_pc(t_process *process, uint32_t move,
						uint8_t two_bits);
void					write_possess(t_vm *vm, uint32_t position, int champ,
						size_t size);

/*
**************
**   FUNC	**
**************
*/
int						live(t_vm *vm, t_process *process, t_args *args);
int						ld(t_vm *vm, t_process *process, t_args *args);
int						st(t_vm *vm, t_process *process, t_args *args);
int						add(t_vm *vm, t_process *process, t_args *args);
int						sub(t_vm *vm, t_process *process, t_args *args);
int						and_(t_vm *vm, t_process *process, t_args *args);
int						or_(t_vm *vm, t_process *process, t_args *args);
int						xor_(t_vm *vm, t_process *process, t_args *args);
int						zjmp(t_vm *vm, t_process *process, t_args *args);
int						ldi(t_vm *vm, t_process *process, t_args *args);
int						sti(t_vm *vm, t_process *process, t_args *args);
int						fork_(t_vm *vm, t_process *process, t_args *args);
int						lld(t_vm *vm, t_process *process, t_args *args);
int						lldi(t_vm *vm, t_process *process, t_args *args);
int						lfork(t_vm *vm, t_process *process, t_args *args);
int						aff(t_vm *vm, t_process *process, t_args *args);
int						norm_dump(t_options *options, int ac, char **av,
							int *i);
int						process_get_func(t_vm *vm, t_process *process);
int						call_function(t_vm *vm, t_process *process);
void					kill_weak_champ_allahu_akbar(t_vm *vm);
int						arg_loop(t_options *options, int ac, char **av);
int						get_dump_and_v(t_options *options, int ac, char **av,
	int *i);
int						set_champ_number(t_options *options, int ac, char **av,
	int *i);

/*
**************
**  PRINT    **
**************
*/
void					print_octet(uint8_t nb);
void					print_dump(t_vm *vm);
void					print_champ_name(t_champion *champ);
void					print_end(t_vm *vm);

/*
**************
**   VISU	**
**************
*/
void					visu_init_vm(t_vm *vm);
void					visu_speed(t_vm *vm, int row, int col);
int						visu_print_string(t_vm *vm, char *str, int col,
						int row);
void					visu_update_vm(t_vm *vm, int position,
						unsigned char *data, int size);
void					visu_update_pc(t_vm *vm, int position, int type);
void					visu_update_process(t_process *process);
void					visu_update_panel(t_vm *vm);
void					fast_terminal(float time, int size, int on_off);
void					visu_wesh_wesh(t_vm *vm, int on_off);
void					call_visu(t_vm *vm, t_process *process, int type);
void					visu_update_head(t_vm *vm);
void					visu_background(t_vm *vm, uint8_t to_do);
void					visu_border(t_vm *vm, uint8_t to_do);
void					visu_refresh(t_vm *vm, uint8_t to_do);
void					visu_erase(t_vm *vm, uint8_t to_do);
int						visu_place_ascii(WINDOW *w_w, char *path,
						int row, int col);
void					visu_print_intro(t_vm *vm);
void					init_ncurses(t_vm *vm);
void					visu_init_colors(void);
void					visu_print_outro(t_vm *vm);
void					control_speed(t_vm *vm);

#endif
