CC			= cc
NAME 		= codexion
CFLAGS 		= -pthread -Wall -Wextra -Werror

OBJ_DIR 	= obj

SRCS 		= src/main.c \
			  src/parser/validate_args.c \
			  src/parser/parse_args.c \
			  src/init/init_sim.c \
			  src/init/free_sim.c \
			  src/sim/helpers.c \
			  src/sim/routine.c

OBJS 		= $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))
HEADERS		= include/codexion.h include/types.h

VPATH 		= src:src/parser:src/init:src/sim

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ_DIR)/%.o: %.c $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@

normie:
	norminette $(SRCS) $(HEADERS)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all normie clean fclean re
