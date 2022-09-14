# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/14 19:27:37 by albzamor          #+#    #+#              #
#    Updated: 2022/09/14 20:43:32 by albzamor         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC	= 	ft_putstr_fd.c ft_putchar_fd.c ft_strmapi.c ft_itoa.c ft_split.c ft_strtrim.c\
 			ft_strjoin.c ft_substr.c ft_atoi.c ft_isalnum.c ft_isdigit.c ft_memchr.c\
			ft_memmove.c ft_strdup.c ft_strlen.c ft_strrchr.c ft_bzero.c ft_isalpha.c\
			ft_isprint.c ft_memcmp.c ft_memset.c ft_strlcat.c ft_strncmp.c ft_tolower.c\
			ft_calloc.c ft_isascii.c ft_memccpy.c ft_memcpy.c ft_strchr.c ft_strlcpy.c\
			ft_strnstr.c ft_toupper.c ft_putendl_fd.c ft_putnbr_fd.c\
			ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c\
			ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
CFLAGS = -Wall -Werror -Wextra
NAME = libft.a
FLAGS = -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\n\n\033[0;32mCompiling libft..."
	@ar rc $(NAME) $^
	@ranlib $(NAME)
	@echo "\033[0m"

%.o: %.c
	@printf "\033[0;33mGenerating libft objects... %-33.33s\r" $@
	@cc ${CFLAGS} -c $< -o $@

clean:
	@rm -f $(OBJ)
fclean: clean
	@rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re