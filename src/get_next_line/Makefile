NAME=get_next_line.a

SRCS=get_next_line.c

OBJS=$(SRCS:.c=.o)

CC=gcc
RM=rm -rf
CFLAGS= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
