SRCS			= minishell.c utils.c ms_input.c

OBJS			=	$(SRCS:.c=.o)

NAME			=	minishell

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror

LIBFT		=		../libft/libft.a

RM				=	rm -rf

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline

$(LIBFT):
			make bonus -C ../libft

clean:
				$(RM) $(OBJS)
				make clean -C ../libft

fclean:			clean
						$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
