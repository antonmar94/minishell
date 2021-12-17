
NAME = minishell
SRCS = ./src/minishell.c \

OBJS = ${SRCS:.c=.o}

CC = cc
CFLAGS = -Wall -Werror -Wextra 
RM = rm -f

all: $(NAME)

%.o: %.c
	$(CC)  $(CFLAGS) -c $< -o $@
$(NAME) : $(OBJS)
	$(CC) -o $(NAME) $^ 

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re