#include "../includes/minishell.h"

int find_command(t_shell *shell)
{
	int i;

	i = -1;
	while (++i < shell->size_c)
	{
		if (ft_strcmp(shell->command, shell->list_commands[i]) == 0)
		{
			execute_command(shell, i);
			return(1);
		} // comparar para cada comando. Hacer una tabla con todos¿?¿?
	}
	return(0);
	//command_error(shell);
}

void execute_command(t_shell *shell, int i)
{
	if (i == 0)
		return;
	else if (i == 1)
		print_pwd();
	else if (i == 2)
		wellcome_header(shell);//hello
	else if (i == 3)
		help(shell);
	else if (i == 4)
		cd(shell);
	else if (i == 5)
		echo(shell);
	else if (i == 6)
		clear_console();
	else if (i == 7)
		export(shell);
	else if (i == 8)
		env(shell);
	else if (i == 9)
		unset(shell);
	else if (i == 10)
		exit_minishell(shell);
}

int system_commmand(t_shell *shell, char **envp)
{
	int 		ex_res;
	char		*env_aux;
	char		*env_dup;
	char		**paths_list;
	t_arglist	*holder_first;
	char		**execute_command;
	int			i;

	i = 0;
	env_aux = *envp;
	while (ft_strncmp(env_aux, "PATH", 4))
		env_aux++;
	env_dup = ft_strdup(env_aux);
	env_dup += 5;
	paths_list = ft_split(env_dup, ':');
	execute_command = malloc(sizeof(char *) * shell->size_args + 2);
	execute_command[0] = (ft_strjoin(ft_strjoin(*paths_list, "/"),
			shell->command));
	i++;
	holder_first = shell->arg_list;
 	while (shell->arg_list->content && shell->size_args > 0)
	{
		execute_command[i] = shell->arg_list->content;
		shell->arg_list = shell->arg_list->next;
		i++;
	}
	execute_command[i] = NULL;
	shell->arg_list = holder_first;
	while (*paths_list)
	{
		ex_res = execve (ft_strjoin(ft_strjoin(*paths_list, "/"),
			shell->command), execute_command, envp);
		paths_list++;
	}
	if(ex_res)
		return (0);
	return (1);
}
