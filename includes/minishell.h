#ifndef LIBMINISHELL_H
# define LIBMINISHELL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <termios.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <errno.h>

# define READ_END	0
# define WRITE_END	1
//# define PIPE_FILE_NAME	"pipe_file.txt"
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
	char		*home_user;
}	t_path;

typedef struct arg_list
{
	char				*content;
	struct arg_list		*next;

}	t_arglist;

typedef struct env_list
{
	char				*var_name;
	char				*var_content;
	struct env_list		*next;

}	t_env_list;

typedef struct pipes_struct
{
	int		fd1[2];
	int		fd2[2];
	char	*holder_parent;
	int		error;

}	t_pipes;

typedef struct s_aux_pointer
{
	int		size_arg;
	int		count_untildollar;
	char	*shell_line_walker;
	char	*origin_line_arg;
	char	*first_dollar_found;
	char	*line_untildollar_joined;
	char 	*line_untildollar;
	char 	*new_expanded_str;
	char 	*content;
	char	*line_walker;
	char	*final_str;

}	t_aux_pointer;

typedef struct s_shell
{
	char 			*line;
	int				size_line;
	char			*command;
	char			*command_flag;
	char			**command_args;
	char			**command_plus_args;
	char			*line_walker;
	int				size_com_args;
	char			**list_commands;
	int				size_c;
	int 			exit;
	int 			exit_return;
	t_path			*path;
	t_arglist		*arg_list;
	t_env_list		*env_list;
	t_env_list		*env_list_plus;
	t_aux_pointer 	*aux_pointer;
	t_pipes			*pipes_struct;
}	t_shell;

void		leaks(void);

/*----------------------- header ---------------------------------------------*/
void		wellcome_header(t_shell *shell);
void		print_header(t_shell *shell, char *custom_head);


/*----------------------- signal----------------------------------------------*/
void		sigint_handler(void);

/*----------------------- init_commands --------------------------------------*/
t_path 		*init_path(t_shell *shell);
t_shell 	*initialice(char** envp);
void 		separate_args_flag(t_shell *shell);
void 		separate_args_no_flag(t_shell *shell);
t_arglist	*arg_node_new(char *first_arg);
void		arglstadd_back(t_arglist **arg_lst, t_arglist *new);
int 		env(t_shell *shell);
int 		unset(t_shell *shell);

/*----------------------- init_env --------------------------------------*/
t_env_list	*env_var_list_new(char* env_var);
void		env_var_add_back(t_env_list **env_list, t_env_list *new);
t_env_list	*init_list_env(t_shell *shell, char** envp);
char 		*cut_env_var_name(char* env_var);
char 		*cut_env_var_content(char* env_var);
int 		look_for_var_name(t_shell *shell, char *var_name_to_find);
int 		change_var_content(t_shell *shell, char *var_name_to_find,
				char *var_content_to_change);

int 		del_var_node_coincident(t_shell *shell, char *var_name_to_find);


int 		do_exec(char *buff, t_shell *shell);

void		clear_console(void);


int			split_arguments(t_shell *shell);
int 		line_without_command(t_shell *shell);
int			arg_listing(t_shell *shell);

int		count_args(t_shell *shell);
int		split_arguments(t_shell *shell);
int 	find_command(t_shell *shell);
int		system_commmand(t_shell *shell, char **envp);
void	execute_command(t_shell *shell, int i);

int 	find_enviro_command(t_shell *shell);

/*--------------------PARSING AND SYNTAX----------------------------------------------------*/
int		check_syntax(t_shell *shell);
int		check_quotes_syntax(char	*line);
int		check_redirect_syntax(char *line);


char	*search_var_coincident(t_shell *shell, char* str_to_find);
char 	*change_dollars(t_shell *shell, char *str_to_change_dollar);
void	nocontent_runaway(t_aux_pointer *pointer);
void 	replace_content_runaway(t_aux_pointer *pointer);
void	replace_dollar(t_shell *shell);

char	this_quote(char *line);
int		check_quotes(char *line_walker, char quotes);
int		size_quotes_arg(char *line_walker, char quotes);
char	check_allquotes(char *line_walker);
int		check_quotes(char *line_walker, char quotes);

int		check_list_flag(char *list_arg);
int		size_argument(t_shell *shell);
int		get_size_part(char	**arg_walker, char **arg_holder, char quotes);
char	*get_arg_part(t_shell *shell, char **arg_walker, char **arg_holder);
char	*arg_creator(t_shell *shell, char **argument);
int		size_quotes_arg(char *line_walker, char quotes);

int		execute_line(t_shell *shell, char **envp);
void 	do_redirect(t_shell *shell, char **envp);

/*----------------------- list_commands --------------------------------------*/

int 	print_pwd(t_shell *shell);
void	help(t_shell *shell);
void	exit_minishell(t_shell *shell);
int 	cd(t_shell *shell);
int 	echo(t_shell *shell);
int 	export(t_shell *shell);

/*----------------------- ERRORS ---------------------------------------------*/
int		syntax_error(t_shell *shell);
int		error_system_pwd(t_shell *shell);
void	command_error(t_shell *shell, char *command);
int		error_number_args(t_shell *shell);
int		error_wrong_path(t_shell *shell);
int		error_too_many_args(void);
int		error_not_numeric(t_shell *shell);
int		error_child_process(t_shell *shell);
int 	identifier_enviro_error(t_shell *shell);

/*----------------------- AUXILIAR--------------------------------------------*/
int		size_matriz(char **str);
void	check_envar(t_shell *shell);
void	*del_name_and_contend(t_shell *shell);
int		check_char(char *str, char char_tofind);

/*----------------------- PIPES AND EXECUTION--------------------------------------------*/
int		check_error_child(t_shell *shell, int pid);
void	pipes_first(t_shell *shell, char **envp, int is_first);
void	pipes_next(t_shell *shell, char **envp, char *holder_child);
char	*pipe_next_line(char *line);
int		check_pipe_syntax(char *line);
char	*create_child_line(t_pipes *pipes_struct);
int		execute_child_line(t_shell *shell, char **envp);
void	child_execution(t_shell *shell, char **envp);
int		execute_all(t_shell *shell, t_pipes *pipes_struct, char **envp);

/*----------------------- AUXILIAR PRINT--------------------------------------*/
void	print_all(t_shell *shell);
void	print_env_list(t_env_list *envp);
void 	print_var_content_text(char *var_name, char *var_content, t_shell *shell);
void 	print_var_unset(char *var_name, t_shell *shell);

/*----------------------- FREE--------------------------------------*/
void	free_parent(t_shell *shell);
void	free_all_struct(t_shell *shell);
void	free_arg_list(t_arglist **arg_lst);
void	free_env_list(t_env_list *envp);
void 	new_free(char **ptr);

/*------------------------ MOD LIFT --------------------------------------*/
char	*ft_strjoin_whith_space(char const *s1, char const *s2);
char	*ft_split_one(char *s, char c, char d);
size_t	ft_desplace_2char(char const *s, char c, char d);
size_t	ft_lens_2char(char *lens, char c, char d);
int		ft_isdigit_str(char *str);
int		ft_isalpha_str(char *str, char c);



/*----------------------- REDIR------------------------------------------*/

void redirect(char *buff);

#endif