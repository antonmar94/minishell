

NAME = minishell
NAME_DEBUG = minishell_debug
CODE_DEBUG_EXTERNAL_CONSOLE = true
LIBFT_NAME = libft.a
LIBFT_DIR = ./libft/
SRCS =	./srcs/main.c \
		./srcs/header.c \
		./srcs/errors.c \
		./srcs/0_init.c \
		./srcs/0b_init_env.c\
		./srcs/0c_signal.c \
		./srcs/1b_search_quotes.c \
		./srcs/2_evaluate_commands.c \
		./srcs/3_command_pwd_cd_exit_help_echo.c \
		./srcs/4_commands_2.c \
		./srcs/z_auxiliar_comp.c \
		./srcs/z1_auxiliar_list.c \
		./srcs/1d_search_dollar.c \
		./srcs/z4_check_aux.c \
		./srcs/z5_aux_lib.c \
		./srcs/z6_aux_free.c \
		./srcs/5_redirect.c \

OBJS = ${SRCS:.c=.o}

UNAME :=$(shell uname -m)
ifeq ($(UNAME), arm64)
CC = arch -x86_64 cc
CFLAGS = -Wall -Werror -Wextra
READLINE = -lreadline
MAKE = arch -x86_64 make
DEBUGGER = lldb
else
READLINE_INSTALL_LOCATION = $(shell brew --prefix readline)
CC = cc
CFLAGS = -Wall -Werror -Wextra -I $(READLINE_INSTALL_LOCATION)/include
DEBUGGER = lldb
READLINE = -lreadline -L $(READLINE_INSTALL_LOCATION)/lib
endif

RM = rm -f

all: $(NAME)
%.o: %.c
	$(CC)  $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT_DIR)$(LIBFT_NAME) $(OBJS)
	$(MAKE) bonus -C $(LIBFT_DIR)
	$(CC) $(LIBFT_DIR)$(LIBFT_NAME) $(READLINE) -o $(NAME) $^


$(LIBFT_DIR)$(LIBFT_NAME): $(LIBFT_DIR)
	make bonus -C $(LIBFT_DIR)

	make -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)

debug:
	$(CC) $(SRCS) $(LIBFT_DIR)$(LIBFT_NAME)  $(READLINE) -g -o $(NAME_DEBUG)

create_code_folder:
	rm -rf .vscode
	mkdir .vscode
	@echo "{\"tasks\":[{\"type\":\"cppbuild\",\"label\":\"Make debug\",\"command\":\"/usr/bin/make\",\"args\":[\"debug\"],\"options\":{\"cwd\":\"\$${workspaceFolder}\"},\"problemMatcher\":[\"\$$gcc\"],\"group\":{\"kind\":\"build\",\"isDefault\":true}}],\"version\":\"2.0.0\"}" > .vscode/tasks.json
	@echo "{\"version\": \"0.2.0\",\"configurations\": [{\"name\": \"gcc - Build and debug active file\",\"type\": \"$(DEBUGGER)\",\"request\": \"launch\",\"program\": \"\$${workspaceFolder}/${NAME_DEBUG}\",\"args\": [],\"stopAtEntry\": false,\"cwd\": \"\$${workspaceFolder}\",\"environment\": [],\"externalConsole\": $(CODE_DEBUG_EXTERNAL_CONSOLE),\"MIMode\": \"lldb\",\"preLaunchTask\": \"Make debug\"}]}" > .vscode/launch.json

compare: all
	@cd tests && ./compare.sh && cd ..

del_history:
	rm -f .history_own
#rm -f ../../.history
test: all
	@cd tests && ./test.sh && cd ..

2test: all
	@cd tests && ./2test.sh && cd ..

fclean: clean
	make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)
	$(RM) $(OBJS)
	$(RM) $(NAME_DEBUG)

re: fclean all

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