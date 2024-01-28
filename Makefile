BIN = bin
NAME = pipex
CC = cc
CFLAG = -Wall -Werror -Wextra -g3
SRC = src/main.c \
	  src/utils.c \
	  src/init.c \
	  src/file_utils.c \
	  src/pipex.c \
	  src/env_utils.c \
	  src/heredoc.c
OBJ = $(SRC:src/%c=$(BIN)/%o)
INCS = ./includes
LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)
LFLAGS = -L$(LIBFT) -lft
IFLAGS = -I $(INCS) -I $(LIBFT_PATH)
UNAME := $(shell uname)
RM = rm -rf

all: $(NAME)

$(BIN)/%.o: src/%.c
	$(CC) -c $< $(CFLAG) $(IFLAGS) -o $@

$(NAME): $(BIN) $(OBJ) | $(LIBFT)
	$(CC) $(OBJ) $(LFLAGS) -o $(NAME)

$(BIN):
	mkdir -p $(BIN)

$(LIBFT):
	@make all -C $(LIBFT_PATH) --no-print-directory

clean:
	$(RM) $(BIN)

fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(LIBFT_PATH) --no-print-directory

re: fclean all

test:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./$(NAME)

show:
	@printf "UNAME		: $(UNAME)\n"
	@printf "NAME		: $(NAME)\n"
	@printf "CC			: $(CC)\n"
	@printf "CFLAG		: $(CFLAG)\n"
	@printf "LFLAGS		: $(LFLAGS)\n"
	@printf "IFLAGS		: $(IFLAGS)\n"
	@printf "SRC		: $(SRC)\n"
	@printf "OBJS		: $(OBJS)\n"

.PHONY: all clean fclean re $(LIBFT)
