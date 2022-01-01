
NAME = minishell
LIBFT_NAME = libft.a
LIBFT_DIR = ./libft/
SRCS =	./srcs/main.c \
		./srcs/header.c \
		./srcs/commands.c \


OBJS = ${SRCS:.c=.o}

UNAME :=$(shell uname -m)
ifeq ($(UNAME), arm64)
CC = arch -x86_64 cc
MAKE = arch -x86_64 make
else
CC = cc
endif

CFLAGS = -Wall -Werror -Wextra
RM = rm -f
all: $(NAME)
%.o: %.c
	$(CC)  $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT_DIR)$(LIBFT_NAME) $(OBJS)
	$(MAKE) bonus -C $(LIBFT_DIR)
	$(CC) $(LIBFT_DIR)$(LIBFT_NAME) -lreadline -o $(NAME) $^

$(LIBFT_DIR)$(LIBFT_NAME): $(LIBFT_DIR)
	make bonus -C $(LIBFT_DIR)

	make -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re

# shell uname -m architecture
# cp $(MLX_DIR)libmlx.dylib need to cp to the root
# m1 rule to compile en m1: firstime copy manual libmlx.dylib
# $@ (target)
# $< (first prerequisite  =dependency)
# $? names all prerequisites that are newer than the target
#	 separated by spaces
# $^ filenames all prerequisites that are newer than the target
# 	separated by spaces
# CC = arch -x86_64 cc  arch -X86_64 to compile in M1 minilibx
# arch -x86_64 $(MAKE) -C $(MLX_DIR)