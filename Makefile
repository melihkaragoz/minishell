SRCS			=	src/main/minishell.c src/utils/minish_utils.c src/exec/minish_exec.c \
					src/parse/minish_set_nodes.c src/parse/minish_token_utils.c src/parse/minish_token_seperator.c \
					src/parse/minish_token.c src/exec/minish_run.c src/exec/minish_signal.c src/redirect/ms_redirections.c \
					src/utils/minish_set_utils.c src/redirect/minish_redirect_utils.c src/exec/minish_builtin_utils.c \
					src/exec/minish_builtin.c src/exec/minish_run_utils.c src/exec/minish_exec_builtin.c \
					src/exec/minish_next_exec_builtin.c src/exec/minish_puts.c

OBJS			=	$(SRCS:.c=.o)

NAME			=	minishell

GNL				=	src/get_next_line/get_next_line.a

LIBFT			=	src/libft/libft.a

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror -g

RM				=	rm -rf

all:			$(NAME)

$(NAME):		$(OBJS) $(LIBFT) $(GNL)
				@$(CC) $(CFLAGS) $(OBJS) $(GNL) $(LIBFT) -o $(NAME) -lreadline
				@echo "\033[0;32mCompiled successfully\033[0m"
				@echo "\033[0;32m./other dizinindeki ./notes.txt'yi okumayi unutma.\n\nTask 1 [processing]\nTask 2 [done]\nTask 3 [done]\n\033[0m"

%.o : %.c
				@$(CC) $(CFLAGS) -c $< -o $@

$(GNL):
				@make -C src/get_next_line

$(LIBFT):
				@make bonus -C src/libft

clean:
				@$(RM) $(OBJS)
				@make clean -C src/libft
				@make clean -C src/get_next_line

fclean:			clean
				@$(RM) $(NAME)
				@make fclean -C src/libft
				@make fclean -C src/get_next_line

re:				fclean $(NAME)

git:			fclean
				@python3 ./other/git.py

.PHONY:			all clean fclean re git
