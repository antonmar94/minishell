#ifndef LIBMINISHELL_H
# define LIBMINISHELL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>

# define GRAY	"\033[1;30m"
# define RED	"\033[1;31m"
# define GREEN	"\033[1;32m"
# define YELLOW	"\033[1;33m"
# define BLUE	"\033[1;34m"
# define PINK	"\033[1;35m"
# define CYAN	"\033[1;36m"
# define WHITE	"\033[0;37m"
# define RESET	"\033[0;m"
# define BOLD	"\033[1;m"
# define BEGIN(x,y) "\033["#x";"#y"m"    // x: fondo, y: primer plano

/*
** minishell variables
*/
typedef struct s_path
{
	char 		*user;
	char		*home;
	char		*home_user;
}	t_path;

typedef struct s_shell
{
	char 		*line;
	char		*command;
	char		*command_flag;
	char		**command_args;
	char		**command_plus_args;
	int			size_line;
	char		**list_commands;
	int			size_c;
	t_path		*path;
}	t_shell;

/*----------------------- init_commands --------------------------------------*/
t_path 	*init_path(t_shell *shell);
t_shell *initialice();
void 	separate_args_flag(t_shell *shell);
void 	separate_args_no_flag(t_shell *shell);




void	header(t_shell *shell);
void	clear_console(void);




void	split_line_to_command(t_shell *shell);
void 	find_command(t_shell *shell);
void	execute_command(t_shell *shell, int i);

/*----------------------- list_commands --------------------------------------*/

int		print_pwd(void);
void	help(t_shell *shell);
void 	exit_minishell(t_shell *shell);
int 	cd(t_shell *shell);
int 	echo(t_shell *shell);



/*----------------------- ERRORS ---------------------------------------------*/
int		error_system_pwd(void);
void	command_error(void);
int		error_number_args(void);
int		error_wrong_path(void);

/*----------------------- AUXILIAR------------------/-------------------------*/
void	print_all(t_shell *shell);

#endif