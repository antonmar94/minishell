NAME = minishell
NAME_DEBUG = minishell_debug
CODE_DEBUG_EXTERNAL_CONSOLE = true
LIBFT_NAME = libft.a
LIBFT_DIR = ./libft/


SRCS = $(wildcard *.c) $(wildcard srcs/*/*.c)
OBJS = $(SRCS:.c=.o)

READLINE_INSTALL_LOCATION = $(shell brew --prefix readline)
CFLAGS = -Wall -Werror -Wextra
MAKE = arch -x86_64 make
DEBUGGER = lldb
OBJECT_FLAGS = -Wall -Werror -Wextra -I $(READLINE_INSTALL_LOCATION)/include
COMP_FLAGS = -Wall -Werror -Wextra -L $(READLINE_INSTALL_LOCATION)/lib #-g3 -fsanitize=address
READLINE = -lreadline

CC = cc

all: $(NAME)

%.o:$(SRC_DIR)%.c
	@printf "\033[0;33mGenerating minishell objects... %-33.33s\r" $@
	@${CC} ${OBJECT_FLAGS} -c $< -o $@

$(NAME): $(OBJS)
	@echo "\n"
	@make -C $(LIBFT_DIR)
	@echo "\033[0;35mCompiling minishell..."
	@$(CC) $(COMP_FLAGS) $(LIBFT_DIR)$(LIBFT_NAME) -lreadline -o $(NAME) $^
	@echo "\n\033[0;32mDone !"
	@echo "set enable-bracketed-paste off" > .inputrc
	@export INPUTRC=$PWD/.inputrc

debug: 
	@$(CC) $(SRCS) $(LIBFT_DIR)$(LIBFT_NAME) -lreadline  -g -o $(NAME_DEBUG)

sani: $(LIBFT_DIR)$(LIBFT_NAME) $(OBJS)
	@$(MAKE) bonus -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS2) $(LIBFT_DIR)$(LIBFT_NAME) -lreadline -o $(NAME) $^

create_code_folder:
	@rm -rf .vscode
	@mkdir .vscode
	@echo "{\"tasks\":[{\"type\":\"cppbuild\",\"label\":\"Make debug\",\"command\":\"/usr/bin/make\",\"args\":[\"debug\"],\"options\":{\"cwd\":\"\$${workspaceFolder}\"},\"problemMatcher\":[\"\$$gcc\"],\"group\":{\"kind\":\"build\",\"isDefault\":true}}],\"version\":\"2.0.0\"}" > .vscode/tasks.json
	@echo "{\"version\": \"0.2.0\",\"configurations\": [{\"name\": \"gcc - Build and debug active file\",\"type\": \"$(DEBUGGER)\",\"request\": \"launch\",\"program\": \"\$${workspaceFolder}/${NAME_DEBUG}\",\"args\": [],\"stopAtEntry\": false,\"cwd\": \"\$${workspaceFolder}\",\"environment\": [],\"externalConsole\": $(CODE_DEBUG_EXTERNAL_CONSOLE),\"MIMode\": \"lldb\",\"preLaunchTask\": \"Make debug\"}]}" > .vscode/launch.json

compare: all
	@cd tests && ./compare.sh && cd ..

del_history:
	@echo "\033[0;33mDeleting History..."
	@rm -f .history_own
	@echo "\033[0;32mDone !"
	@echo "\033[0m"

clean:
	@echo "\033[0;31mCleaning libft..."
	@make clean -C libft/
	@echo "\nRemoving objects..."
	@rm -f $(OBJS)
	@echo "\n\033[0;32mDone !"
	@echo "\033[0m"

fclean:
	@echo "\033[0;31mCleaning libft..."
	@make fclean -C libft/
	@echo "\nDeleting objects..."
	@rm -f $(OBJS)
	@echo "\nDeleting executable..."
	@rm -f $(NAME)
	@echo "\n\033[0;32mDone !"
	@echo "\033[0m"

re: fclean all

.PHONY: all clean fclean re

#Colors
BLACK		:="\033[0;30m"
RED			:="\033[0;31m"
GREEN		:="\033[0;32m"
BROWN		:="\033[0;33m"
BLUE		:="\033[0;34m"
PURPLE		:="\033[0;35m"
CYAN		:="\033[0;36m"
LIGHT_GRAY	:="\033[0;37m"
DARK_GRAY	:="\033[1;30m"
LIGHT_RED	:="\033[1;31m"
LIGHT_GREEN	:="\033[1;32m"
YELLOW		:="\033[1;33m"
LIGHT_BLUE	:="\033[1;34m"
LIGHT_PURPLE:="\033[1;35m"
LIGHT_CYAN	:="\033[1;36m"
WHITE		:="\033[1;37m"
RESET		:="\x1b[0m"

#.PHONY only execute somethhing not create files
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