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
typedef struct s_shell
{
	char 		*line;
	char		**commands;
	int			size_c;
}	t_shell;

void	header(void);
void	clear_console(void);
void	find_command(t_shell *shell);
void	execute_command(t_shell *shell, int i);

/*----------------------- COMMANDS ---------------------------------------------*/

int		print_pwd(void);
void	help(t_shell *shell);
void 	exit_minishell(void);



/*----------------------- ERRORS ---------------------------------------------*/
int		error_system_pwd(void);
void	command_error(t_shell *shell);

#endif