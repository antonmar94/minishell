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

		//char *whereis[] = {"whereis", NULL};
		//char *cmd[] = { "echo", "hola", (char *)0 };
		//char *env[] = { "TERM=xterm", (char *)0 };
		//salida =
		//execve("/var/clear", cmd, envp);
	int ex_res;
	int pid;

	pid = fork();// Crea un proceso hijo, reemplaza el programa en el proceso hijo
	if (pid < 0)
		return (0);
	if(pid == 0) //PID=0 es el hijo
	{
		//printf("\narg1: %s\n",  shell->command_plus_args[1]);
		ex_res = execve (ft_strjoin("/bin/", shell->command), shell->command_plus_args, envp);
		if(ex_res)
			return (0);
	}
	waitpid(pid, NULL, 0);// Espera a que salga el proceso hijo
	return (1);
}
