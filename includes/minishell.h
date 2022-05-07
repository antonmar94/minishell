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
	char			*command;
	char			*command_flag;
	char			**command_args;
	char			**command_plus_args;
	int				size_line;
	char			*line_walker;
	int				size_args;
	char			**list_commands;
	int				size_c;
	int 			exit;
	int 			exit_return;
	t_path			*path;
	t_arglist		*arg_list;
	t_env_list		*env_list;
	t_aux_pointer 	*aux_pointer;

}	t_shell;

void	leaks(void);

/*----------------------- header ---------------------------------------------*/
void	wellcome_header(t_shell *shell);
void	print_header(t_shell *shell, char *custom_head);


/*----------------------- signal----------------------------------------------*/
void	sigint_handler(void);

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

char	check_allquotes(char *line_walker);
int		count_args(t_shell *shell);
int		split_arguments(t_shell *shell);
int 	find_command(t_shell *shell);
int		system_commmand(t_shell *shell, char **envp);
void	execute_command(t_shell *shell, int i);
void	free_and_reset_values(t_shell *shell);

/*--------------------PARSING----------------------------------------------------*/
int		check_quotes_error(char	*line);
char	*search_var_coincident(t_shell *shell, char* str_to_find);
char 	*change_dollars(t_shell *shell, char *str_to_change_dollar);
void	nocontent_runaway(t_aux_pointer *pointer);
void 	replace_content_runaway(t_aux_pointer *pointer);
void	replace_dollar(t_shell *shell);

int		check_quotes(char *line_walker, char quotes);
char	check_allquotes(char *line_walker);
int		size_quotes_arg(char *line_walker, char quotes);
int		count_quotes(t_shell *shell);
char 	*del_quotes(char *str_to_del_quotes);

int	execute_line(t_shell *shell, char **envp);
void do_redirect(t_shell *shell, char **envp);

/*----------------------- list_commands --------------------------------------*/

int		print_pwd(void);
void	help(t_shell *shell);
void	exit_minishell(t_shell *shell);
int 	cd(t_shell *shell);
int 	echo(t_shell *shell);
int 	export(t_shell *shell);
void	all_clear(t_arglist **arg_lst);



/*----------------------- ERRORS ---------------------------------------------*/
int		syntax_error(void);
int		error_system_pwd(void);
void	command_error(char *error);
int		error_number_args(void);
int		error_wrong_path(void);
int		error_too_many_args(void);
int		error_not_numeric(void);
int		error_child_process(void);

/*----------------------- AUXILIAR--------------------------------------------*/

int		size_matriz(char **str);
void	check_envar(t_shell *shell);
void	free_all(t_shell *shell);
void	*del_name_and_contend(t_shell *shell);
void	free_env_list(t_env_list *envp);
void	free_aux_pointer(t_aux_pointer *aux_pointer);
void 	new_free(char **ptr);
int		check_char(char *str, char char_tofind);



/*----------------------- AUXILIAR PRINT--------------------------------------*/
void	print_all(t_shell *shell);
void	print_env_list(t_env_list *envp);
void 	print_var_content_text(char *var_name, char *var_content, t_shell *shell);
void 	print_var_unset(char *var_name, t_shell *shell);





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