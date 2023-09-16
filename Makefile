SRCS			=	src/minishell.c src/minish_utils.c src/minish_exec.c \
					src/minish_set_nodes.c src/minish_token_utils.c src/minish_token_seperator.c \
					src/minish_token.c src/minish_run.c

OBJS			=	$(SRCS:.c=.o)

NAME			=	minishell

LIBFT			=	libft/libft.a

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror -g

LIBFT			=	libft/libft.a

RM				=	rm -rf

all:			$(NAME)

$(NAME):		$(OBJS) $(LIBFT)
				@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline
				@echo "\033[0;32mCompiled successfully\033[0m"

%.o : %.c
				@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
				@make bonus -C libft

clean:
				@$(RM) $(OBJS)
				@make clean -C libft

fclean:			clean
				@$(RM) $(NAME)
				@make fclean -C libft

re:				fclean $(NAME)

git:			fclean
				@python3 ./other/git.py

.PHONY:			all clean fclean re git
