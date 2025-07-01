##
## EPITECH PROJECT, 2025
## Corewar-pierre.baud/mathieu_girard
## File description:
## Makefile
##

SRC		=		src/main.c \
				src/annexe/annexe.c \
				src/annexe/annexe_core.c \
				src/annexe/annexe_core2.c \
				src/annexe/annexe_define_value.c \
				src/parsing.c \
				src/read_header.c \
				src/load_champions.c \
				src/instruction/and_st.c \
				src/instruction/aff_lfork_lldi.c \
				src/instruction/ld_live_add.c \
				src/instruction/ldi.c \
				src/instruction/sti_fork_lld.c \
				src/instruction/sub_zjmp.c \
				src/instruction/xor_or.c \
				src/execute_game.c \
				src/annexe/annexe_game.c \
				src/run_game.c \
				src/dump_memory.c \



OBJ 	=		$(SRC:.c=.o)

CFLAGS  = -Wall -Wextra -lncurses -g3

NAME    = 		corewar

all: 	$(NAME)

$(NAME): 		$(OBJ)
		gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)
		rm -f $(OBJ)

re: 	fclean all
