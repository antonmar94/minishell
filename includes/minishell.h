/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 16:38:47 by albzamor          #+#    #+#             */
/*   Updated: 2022/10/04 21:13:08 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# define O_TMPFILE 020000000
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

typedef struct s_path
{
	char	*user;
	char	*home_user;
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

typedef struct pipes_struct ///32 
{
	pid_t	pid;
	int		fd_red[2];
	int		fd_in[2];
	int		fd1[2];
	int		fd2[2];
	int		last_arrows;
	char	*heardoc_lines;
	char	**all_files;
	char	**simple_files;
	char	*holder_parent;
	char	*child_line;
	int		child_counter;
	int		error;
}	t_pipes;

typedef struct s_aux_p
{
	int		size_arg;
	int		size_predollar;
	char	*line_walker;
	char	*org_line_arg;
	char	*first_dollar_found;
	char	*line_predolar_joined;
	char	*line_predolar;
	char	*new_expanded;
	char	*content;
	char	*final_str;

}	t_aux_p;

typedef struct s_shell
{
	char			*line;
	char			*sig_int_line;
	char			*command;
	char			*command_flag;
	char			**command_args;
	char			**command_plus_args;
	char			*line_walker;
	int				size_com_args;
	char			**list_commands;
	int				size_c;
	int				exit;
	int				exit_return;
	int				has_pipes;
	t_path			*path;
	t_arglist		*arg_list;
	char			*free_aux_list;
	t_env_list		*env_list;
	t_env_list		*env_list_plus;
	t_env_list		*env_list_ordered;
	t_aux_p			*aux_p;
	t_pipes			*pipes_struct;
	char			**minishell_envp;
}	t_shell;

void		leaks(void);

/*----------------------- header ---------------------------------------------*/
void		wellcome_header(t_shell *shell);
void		print_header(t_shell *shell, char *custom_head);

/*----------------------- signal----------------------------------------------*/
void		sigint_handler(int sig);
void		signal_handler(void);
void		sigquit_handler(int sig);

/*----------------------- init_commands --------------------------------------*/
char		**mini_enviro(void);
t_path		*init_path(t_shell *shell);
t_shell		*initialice(char **envp);
void		separate_args_flag(t_shell *shell);
void		separate_args_no_flag(t_shell *shell);
t_arglist	*arg_node_new(char *first_arg);
void		arglstadd_back(t_arglist **arg_lst, t_arglist *new);
int			env(t_shell *shell);
int			unset(t_shell *shell);

/*----------------------- init_env ------------------------------------------*/
t_env_list	*env_var_list_new(char *env_var);
void		env_var_add_back(t_env_list **env_list, t_env_list *new);
t_env_list	*init_list_env(t_shell *shell, char **envp);
char		*cut_env_var_name(char *env_var);
char		*cut_env_var_content(char *env_var);
int			change_var_content(t_shell *shell, char *var_name_to_find,
				char *var_content_to_change);
int			varname_found(char **var_name, char	**var_content, t_shell *shell);
int			del_var_node_coincident(t_shell *shell, char *var_name_to_find);
int			do_exec(char *buff, t_shell *shell);
void		clear_console(void);
int			split_arguments(t_shell *shell);
int			line_without_command(t_shell *shell);
int			arg_listing(t_shell *shell);

void		shell_execution(t_shell *shell);
void		ft_new_line(t_shell *shell);
int			count_args(t_shell *shell);
int			split_arguments(t_shell *shell);
int			find_command(t_shell *shell);
int			system_commmand(t_shell *shell, char **envp);
void		execute_command(t_shell *shell, int i);
char		**create_env_matrix(t_shell *shell);
int			find_enviro_command(t_shell *shell);
int			export_util(char *name, char *content, t_shell *shell);
t_env_list	*env_var_list_new_char(char *var_name, char *var_content);
int			env_list_len(t_shell *shell);
void		sort_env(t_shell *shell, int env_list_len);
t_env_list	*order_env_list(t_env_list *env_list);
t_env_list	*return_copy_order_list(t_env_list *env_list);

/*--------------------PARSING AND SYNTAX--------------------------------------*/
int			check_syntax(t_shell *shell);
int			check_quotes_syntax(char	*line);
int			check_redirect_syntax(char *line);

char		*search_var_coincident(t_shell *shell, char *str_to_find);
char		*change_dollars(t_shell *shell, char *str_to_change_dollar);
void		nocontent_runaway(t_aux_p *pointer);
void		replace_content_runaway(t_aux_p *pointer);
void		replace_dollar(t_shell *shell);

char		this_quote(char *line);
char		*last_arg(t_arglist *arg_list);
int			check_quotes(char *line_walker, char quotes);
int			size_quotes_arg(char *line_walker, char quotes);
char		check_allquotes(char *line_walker);
int			check_quotes(char *line_walker, char quotes);
char		*find_dollar_quotes(char *argument);

int			check_list_flag(char *list_arg);
int			check_arg_flag(t_shell *shell, char *argument, int no_add_flag);
int			get_add_flag(int no_add_flag, t_shell *shell);
int			size_argument(t_shell *shell);
int			get_size_part(char	**arg_walker, char **arg_holder, char quotes);
char		*get_arg_part(t_shell *shell, char **arg_walker, char **arg_holder);
char		*arg_creator(t_shell *shell, char **argument);
int			size_quotes_arg(char *line_walker, char quotes);
int			check_arrow_syntax(char *line, char arrow);
int			execute_line(t_shell *shell, char **envp);
int			do_redirect(t_shell *shell);

/*----------------------- list_commands --------------------------------------*/

int			print_pwd(t_shell *shell);
void		help(t_shell *shell);
void		exit_minishell(t_shell *shell);
int			cd(t_shell *shell);
int			echo(t_shell *shell);
int			export(t_shell *shell);
void		exit_return(t_shell *shell);
int			unset_util(char *var_to_unset, t_shell *shell);

/*----------------------- ERRORS ---------------------------------------------*/

int			ft_error(t_shell *shell, char *elem_err, int error_code);
int			syntax_error(t_shell *shell);
void		command_error(t_shell *shell, char *command);
int			error_wrong_path(t_shell *shell, char *line);
int			error_too_many_args(t_shell *shell);
int			error_not_numeric(t_shell *shell);
int			identifier_enviro_error(t_shell *shell);
int			check_error_child(t_shell *shell, int pid);
void		error_args_init(void);
void		error_permission(t_shell *shell, char *file);

/*----------------------- AUXILIAR--------------------------------------------*/
int			size_matriz(char **str);
void		*del_name_and_contend(t_shell *shell);
int			check_char(char *str, char char_tofind);
void		print_env_list(t_env_list *envp);
void		print_env_list_export(t_env_list *envp);
int			env_export(t_shell *shell);
int			ft_lst_env_size(t_env_list *lst);
void		check_new_minishell(t_shell *shell);
int			export_one(t_shell *shell, char *var_name, char *var_content);

/*----------------------- PIPES AND EXECUTION---------------------------------*/
int			get_size_line(char *size_walker);
void		pipes_first(t_shell *shell, char **envp, int is_first);
void		pipes_next(t_shell *shell, char **envp, char *child_line);
char		*pipe_next_line(char *line);
int			check_pipe_syntax(t_shell *shell);
char		*create_child_line(t_pipes *pipes_struct);
int			execute_child_line(t_shell *shell, char **envp);
void		child_execution(t_shell *shell, char **envp);
int			create_child(t_shell *shell, t_pipes *pipes_struct, int fd);
int			execute_all(t_shell *shell, t_pipes *pipes_struct, char **envp);

/*----------------------- FREE------------------------------------------------*/
void		free_parent(t_shell *shell);
void		free_all_struct(t_shell *shell, char **envp);
void		free_arg_list(t_arglist **arg_lst);
void		free_env_list(t_env_list *envp);
void		new_free(char **ptr);
void		free_matrix(char **array);

/*------------------------ MOD LIFT -----------------------------------------*/
char		*ft_split_one(char *s, char c, char d);
size_t		ft_desplace_2char(char const *s, char c, char d);
size_t		ft_lens_2char(char *lens, char c, char d);
int			ft_isdigit_str(char *str);
int			ft_strcmp(const char *s1, const char *s2);
void		free_env_list2(t_env_list *envp);

/*----------------------- REDIR----------------------------------------------*/

int			check_file_error(t_shell *shell, int fd, char *all_files);
int			jump_quotes(char **line_to_ignore);
int			check_redirect(char **line, char **rest_of_line, char arrow);
void		append_to_line(char **line, char **line_finder, char arrow);
void		get_line_execute(char **line, char **rest_of_line, char arrow);
int			get_create_files(t_shell *shell, char **rest_of_line,
				int num_arrows);
char		*get_heardoc_lines(t_shell *shell, char **all_files);
int			check_last(char **aux_finder, char arrow);
char		*ask_for_line(t_shell *shell, char *all_files);
int			get_matrix_size(char *line, char *arrows);
char		*get_file_name(t_shell *shell, char *child_line);
char		**get_files_matrix(t_shell *shell, char *child_line, char *arrows);
int			get_clean_line(char **line, char *arrows);
int			last_num_arrows(char *line);
int			create_file(t_shell *shell, char *file_in_line, int file_size);
int			redirect_resolution(t_shell *shell, t_pipes *pipes_struct);
int			do_redirect(t_shell *shell);
int			simple_indirect(t_shell *shell);
int			double_indirect(t_shell *shell);

/*----------------------- HEARDOC--------------------------------------------*/
char		*first_line_in(t_shell *shell, char ***all_files,
				char **all_lines);
char		*next_line_in(t_shell *shell, char ***all_files, char **all_lines);
int			check_interactive(t_shell *shell, char **line_in);

extern int	g_interactive;
#endif