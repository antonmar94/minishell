# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/14 19:27:37 by albzamor          #+#    #+#              #
#    Updated: 2021/08/21 16:57:57 by albzamor         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC	= 	ft_putstr_fd.c ft_putchar_fd.c ft_strmapi.c ft_itoa.c ft_split.c ft_strtrim.c\
 			ft_strjoin.c ft_substr.c ft_atoi.c ft_isalnum.c ft_isdigit.c ft_memchr.c\
			ft_memmove.c ft_strdup.c ft_strlen.c ft_strrchr.c ft_bzero.c ft_isalpha.c\
			ft_isprint.c ft_memcmp.c ft_memset.c ft_strlcat.c ft_strncmp.c ft_tolower.c\
			ft_calloc.c ft_isascii.c ft_memccpy.c ft_memcpy.c ft_strchr.c ft_strlcpy.c\
			ft_strnstr.c ft_toupper.c ft_putendl_fd.c ft_putnbr_fd.c

SRC_BONUS	= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c\
			ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

NAME = libft.a
FLAGS = -Wall -Wextra -Werror
OBJ = $(SRC:.c=.o)
OBJ_B = $(SRC_BONUS:.c=.o)
all: $(NAME)
$(OBJ): $(SRC)
	gcc $(FLAGS) -c $(SRC)
$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)
bonus: $(OBJ_B) $(OBJ)
	ar rcs $(NAME) $(OBJ_B) $(OBJ)
$(OBJ_B): $(SRC_BONUS)
	gcc $(FLAGS) -c $(SRC_BONUS)
clean:
	rm -f $(OBJ) $(OBJ_B)
fclean: clean
	rm -f $(NAME) $(OBJ) $(OBJ_B)
re: fclean all bonus
.PHONY: all bonus clean fclean re
