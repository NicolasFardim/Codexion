CC = gcc
BIN = codexion
CFLAGS = -Wall -Wextra -Werror

OBJ_DIR = obj

SRCS = main.c \
		parser.c \

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(BIN)

$(OBJ_DIR):
	mkdir -p $@


$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ_DIR)/%.o: %.c codexion.h data_structures.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

normie:
	norminette $(SRCS)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(BIN)

re: fclean all

.PHONY: all normie clean fclean re
