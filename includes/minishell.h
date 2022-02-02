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

typedef struct arg_list
{
	char			*content;
	struct arg_list	*next;

}	t_arglist;

typedef struct env_list
{
	char				*var_name;
	char				*var_content;
	struct env_list	*next;

}	t_env_list;

typedef struct s_shell
{
	char 		*line;
	char		*line_walker;
	char		*line_args;
	char		*command;
	char		*command_flag;
	char		**command_args;
	char		**command_plus_args;
	int			size_line;
	int			size_args;
	char		**list_commands;
	int			size_c;
	int 		exit;
	t_path		*path;
	t_arglist	*arg_list;
	t_env_list	*env_list;
}	t_shell;

/*----------------------- header ---------------------------------------------*/
void	header(t_shell *shell);
void	print_header(t_shell *shell);


/*----------------------- init_commands --------------------------------------*/
t_path 		*init_path(t_shell *shell);
t_shell 	*initialice(char** envp);
void 		separate_args_flag(t_shell *shell);
void 		separate_args_no_flag(t_shell *shell);
t_arglist	*arg_node_new(char *first_arg);
void		arglstadd_back(t_arglist **arg_lst, t_arglist *new);
t_env_list	*env_var_list_new(char* env_var);
void		env_var_add_back(t_env_list **env_list, t_env_list *new);
t_env_list	*init_list_env(t_shell *shell, char** envp);




void	clear_console(void);



int 	line_without_command(t_shell *shell);
int		arg_listing(t_shell *shell);
int		check_quotes(t_shell *shell, char quotes);
int		count_quotes(t_shell *shell);
int		get_next_argument(t_shell *shell);
int		count_args(t_shell *shell);
int		split_arguments(t_shell *shell);
void	split_line_to_command(t_shell *shell);
void 	find_command(t_shell *shell);
void	execute_command(t_shell *shell, int i);
void	free_and_reset_values(t_shell *shell);

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
void	print_env_list(t_env_list *envp);
int		size_matriz(char **str);

#endif