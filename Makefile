#########################################################################################
###################################### CONSTANTES #######################################
#########################################################################################
NAME_LIB=libcorewar.a
NAME_COREWAR=corewar
NAME_ASM=asm

HEADER_FOLDER=./includes
OBJ_FOLDER=./obj

LIBFT_DIR=./libft

CC=gcc
CFLAGS=-Wall -Wextra -Werror

INCLUDE_PATH=-I$(HEADER_FOLDER) -I$(LIBFT_DIR)/includes
COMPILER=$(CC) $(CFLAGS) $(INCLUDE_PATH)

LIBS =  $(LIBFT_DIR)/libft.a $(NAME_LIB)

#########################################################################################
################################### FICHIERS SOURCES ####################################
#########################################################################################
SRCS_LIB_FOLDER=./srcs/lib
SRCS_ASM_FOLDER=./srcs/asm
SRCS_COREWAR_FOLDER=./srcs/corewar

INCLUDES=arena.h \
	doigts_dans_le_cul_de_la_norminette.h \
	lib.h \
	op.h \
	parser.h

SRCS_LIB_FILES=endian.c \
	op.c \
	round_next_four.c

SRCS_ASM_FILES=binary.c \
	binary_debug.c \
	binary_export.c \
	binary_seek.c \
	binary_write.c \
	main_asm.c \
	parser.c \
	parser_args.c \
	parser_debug.c \
	parser_error.c \
	parser_export.c \
	parser_free.c \
	parser_header.c \
	parser_instruction.c \
	parser_label.c \
	parser_main.c \
	parser_search.c \
	parser_tools.c \
	atoi_move.c

SRCS_COREWAR_FILES=aa_01_live.c \
	aa_02_ld.c \
	aa_03_st.c \
	aa_04_add.c \
	aa_05_sub.c \
	aa_06_and.c \
	aa_07_or.c \
	aa_08_xor.c \
	aa_09_zjmp.c \
	ab_0a_ldi.c \
	ab_0b_sti.c \
	ab_0c_fork.c \
	ab_0d_lld.c \
	ab_0e_lldi.c \
	ab_0f_lfork.c \
	ab_10_aff.c \
	arg_get.c \
	arg_load.c \
	arg_type_test.c \
	eh_merce_la_norme.c \
	init.c \
	init_args.c \
	main_arena.c \
	print.c \
	process_access.c \
	process_cycle.c \
	process_utils.c \
	read_champ.c \
	read_champ_tools.c \
	tool_converters.c \
	usage_corewar.c \
	visu.c \
	visu_ascii.c \
	visu_base.c \
	visu_init.c \
	visu_input.c \
	visu_intro.c \
	visu_print_string.c \
	visu_process.c \
	visu_speed.c \
	visu_vm.c \
	vm_access.c \
	vm_cycle.c

RELINK_INCUDE=$(addprefix $(HEADER_FOLDER)/, $(INCLUDES))
SRCS_LIB=$(addprefix $(SRCS_LIB_FOLDER)/, $(SRCS_LIB_FILES))
SRCS_ASM=$(addprefix $(SRCS_ASM_FOLDER)/, $(SRCS_ASM_FILES))
SRCS_COREWAR=$(addprefix $(SRCS_COREWAR_FOLDER)/, $(SRCS_COREWAR_FILES))

OUT_LIB=$(addprefix $(OBJ_FOLDER)/,$(notdir $(SRCS_LIB:.c=.o)))
OUT_ASM=$(addprefix $(OBJ_FOLDER)/,$(notdir $(SRCS_ASM:.c=.o)))
OUT_COREWAR=$(addprefix $(OBJ_FOLDER)/,$(notdir $(SRCS_COREWAR:.c=.o)))

#########################################################################################
##################################### COMPILATION #######################################
#########################################################################################
all: $(OBJ_FOLDER) $(LIBFT_DIR)/libft.a $(NAME_LIB) $(NAME_ASM) $(NAME_COREWAR)

$(OBJ_FOLDER):
	@mkdir $(OBJ_FOLDER)

$(LIBFT_DIR)/libft.a: FORCE
	@make -C $(LIBFT_DIR)

## LIB
$(NAME_LIB): $(OUT_LIB) $(LIBFT_DIR)/libft.a Makefile $(RELINK_INCUDE)
	ar rc $(NAME_LIB) $(OUT_LIB)

$(OBJ_FOLDER)/%.o: $(SRCS_LIB_FOLDER)/%.c Makefile $(RELINK_INCUDE)
	$(COMPILER) -o $@ -c $<

## ASM
$(NAME_ASM): $(OUT_ASM) $(NAME_LIB) Makefile $(RELINK_INCUDE)
	$(COMPILER) -o $(NAME_ASM) $(OUT_ASM) $(LIBS)

$(OBJ_FOLDER)/%.o: $(SRCS_ASM_FOLDER)/%.c Makefile $(RELINK_INCUDE)
	$(COMPILER) -o $@ -c $<

## COREWAR
UNAME_S    = $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
   LIBS += -l termcap
else
   LIBS += -l ncurses
endif

$(NAME_COREWAR): $(OUT_COREWAR) $(NAME_LIB) Makefile $(RELINK_INCUDE)
	$(COMPILER) -o $(NAME_COREWAR) $(OUT_COREWAR) $(LIBS)

$(OBJ_FOLDER)/%.o: $(SRCS_COREWAR_FOLDER)/%.c Makefile $(RELINK_INCUDE)
	$(COMPILER) -o $@ -c $<

#########################################################################################
######################################## CLEAN ##########################################
#########################################################################################
clean:
	rm -rf $(OBJ_FOLDER)
	rm -f $(NAME_LIB)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME_ASM)
	rm -f $(NAME_COREWAR)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

FORCE:
