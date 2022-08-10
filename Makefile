
NAME = minishell
NAME_DEBUG = minishell_debug
CODE_DEBUG_EXTERNAL_CONSOLE = true
LIBFT_NAME = libft.a
LIBFT_DIR = ./libft/
SRCS =	./srcs/00_init.c \
		./srcs/01_init_env.c \
		./srcs/02_search_quotes.c \
		./srcs/02a_search_quotes_utils.c \
		./srcs/02b_quotes_utils.c \
		./srcs/03_search_dollar.c\
		./srcs/04_evaluate_syntax.c \
		./srcs/04b_evaluate_syntax_2.c \
		./srcs/05_evaluate_commands.c \
		./srcs/06_builtins.c \
		./srcs/07_enviroment_builtins.c \
		./srcs/08_pipes_utils.c \
		./srcs/09_pipes_execution.c \
		./srcs/10_redirect.c \
		./srcs/10b_redirect_utils.c \
		./srcs/11_indirect.c \
		./srcs/11b_indirect_utils.c \
		./srcs/20_header.c \
		./srcs/21_errors.c \
		./srcs/22_errors_2.c \
		./srcs/23_list_utils.c \
		./srcs/24_signals.c \
		./srcs/30_free_utils.c \
		./srcs/31_free_utils_2.c \
		./srcs/al_auxiliar_comp.c \
		./srcs/al_auxiliar_list.c \
		./srcs/al_auxiliar_list2.c \
		./srcs/al_aux_lib.c \
		./srcs/main.c \

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
CFLAGS = -Wall -Werror -Wextra -I $(READLINE_INSTALL_LOCATION)/include #-g3 -fsanitize=address
DEBUGGER = gdb
READLINE = -lreadline -L $(READLINE_INSTALL_LOCATION)/lib
endif

RM = rm -f

all: $(NAME)
%.o: %.c
	$(CC)  $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT_DIR)$(LIBFT_NAME) $(OBJS)
	$(MAKE) bonus -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(LIBFT_DIR)$(LIBFT_NAME) $(READLINE) -o $(NAME) $^


$(LIBFT_DIR)$(LIBFT_NAME): $(LIBFT_DIR)
	make bonus -C $(LIBFT_DIR)

	make -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)

	@echo "set enable-bracketed-paste off" > .inputrc
	export INPUTRC=$PWD/.inputrc

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