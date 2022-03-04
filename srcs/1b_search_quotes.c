/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1b_search_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 19:13:39 by antonmar          #+#    #+#             */
/*   Updated: 2022/03/04 17:42:36 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_quotes(char *line_walker, char quotes) //Devuelve 1 si existen comillas abiertas y cerradas
{
	char	*quotes_finder;

	quotes_finder = line_walker;
	if (*quotes_finder == quotes)
	{
		quotes_finder++;
		while (*quotes_finder)
		{
			if (*quotes_finder == quotes)
				return (1);
			quotes_finder++;
		}
	}
	return (0);
}

int	size_quotes_arg(char *line_walker, char quotes) //Devuelve el tamaño del argumento entre comillas
{
	int		i;
	char	*quotes_finder;

	i = 0;
	quotes_finder = line_walker;
	if (check_quotes(line_walker, quotes))
	{
		quotes_finder++;
		while (*quotes_finder)
		{
			if (*quotes_finder == quotes)
				return (i);
			i++;
			quotes_finder++;
		}
	}
	return (0);
}

char	check_allquotes(char *line_walker)
{
	char *aux;

	aux = line_walker;
	if (check_quotes(aux, '\''))
		return ('\'');
	if (check_quotes(aux, '\"'))
		return ('\"');
	return (0);
}

char jump_quotes(t_shell *shell)
{
	int	i;
	char quotes;

	i = 0;
	quotes = check_allquotes(shell->line_walker);
	while (*shell->line_walker && quotes)
	{
		i = size_quotes_arg(shell->line_walker, quotes);
		if (*shell->line_walker && !i)
			shell->line_walker += 2;
		else if (i)
		{
			shell->line_walker++;
			return (quotes);
		}
		quotes = check_allquotes(shell->line_walker);
	}
	return (0);
}

char jump_flag_quotes(char *flag_line)
{
	int	i;
	char quotes;

	i = 0;
	quotes = check_allquotes(flag_line);
	while (*flag_line && quotes)
	{
		i = size_quotes_arg(flag_line, quotes);
		if (*flag_line && !i)
			flag_line += 2;
		else if (i)
		{
			flag_line++;
			return (quotes);
		}
		quotes = check_allquotes(flag_line);
	}
	return (0);
}

void	check_flag(t_shell *shell) //Comprueba si existe la flag -n en echo y si existe la introduce en "shell->command_flag"
{
	char 	*flag;
	char 	*start_flag;
	char	*no_flag;
	//char 	*end_command;
	char	quotes;
	int		size_flag;
	int 	i;

	i = 0;
	no_flag = shell->line_walker;
	size_flag = 0;
	while (*shell->line_walker && *shell->line_walker == ' ')
		shell->line_walker++;
	quotes = jump_quotes(shell);
	size_flag = 0;
	start_flag = shell->line_walker;
	while (*shell->line_walker && *shell->line_walker != quotes && *shell->line_walker != ' ')
	{
		shell->line_walker++;
		size_flag++;
	}
	if (quotes)
		shell->line_walker++;
	quotes = jump_quotes(shell);
	start_flag = ft_substr(start_flag, 0, size_flag);
	flag = start_flag;
	//printf("flag:%s\n", flag);
	printf("flag line:%s\n", shell->line_walker);
	while (*shell->line_walker != quotes && *shell->line_walker != ' ')
	{
		//printf("line walker:%s\n", shell->line_walker);
		size_flag = 0;
		start_flag = shell->line_walker;
		while (*shell->line_walker && *shell->line_walker != quotes && *shell->line_walker != ' ')
		{
			shell->line_walker++;
			size_flag++;
		}
		if (quotes)
			shell->line_walker++;
		//printf("start_command: %s\n", start_command);
		//printf("size_command: %i\n", size_command);
		quotes = jump_quotes(shell);
		start_flag = ft_substr(start_flag, 0, size_flag);
		//printf("star_flag:%s", start_flag);
		//printf("start command:%s\n", start_command);
		//printf("command:%s\n", command);
		flag = ft_strjoin(flag, start_flag);
	}
	//printf("flag:%s\n", flag);
	if (ft_strcmp(flag, "-n"))
		shell->line_walker = no_flag;
}


int	add_command(t_shell *shell) // arreglar este método, no funciona con 'echo' hola
{
	char 	*command;
	char 	*start_command;
	//char 	*end_command;
	char	quotes;
	int		size_command;
	int i;

	i = 0;
	size_command = 0;
	shell->line_walker = shell->line;
	while (*shell->line_walker && *shell->line_walker == ' ')
		shell->line_walker++;
	quotes = jump_quotes(shell);
	size_command = 0;
	start_command = shell->line_walker;
	while (*shell->line_walker && *shell->line_walker != ' ' && *shell->line_walker != '\"' && *shell->line_walker != '\'')
	{
		//printf("line walker:%s\n", shell->line_walker);
		shell->line_walker++;
		size_command++;
	}
	//if (quotes)
	//	shell->line_walker++;
	quotes = jump_quotes(shell);
	//printf("line walker:%s\n", shell->line_walker);
	//printf("start command:%s\n", start_command);
	//printf("size_command: %i\n", size_command);
	start_command = ft_substr(start_command, 0, size_command);
	command = start_command;
	printf("line walker:%s\n", shell->line_walker);
	//printf("command:%s\n", command);
	while (*shell->line_walker && *shell->line_walker != ' ' && *shell->line_walker != '\"' && *shell->line_walker != '\'')
	{
		//printf("line walker:%s\n", shell->line_walker);
	printf("comillas: %c\n", quotes);
		size_command = 0;
		start_command = shell->line_walker;
		while (*shell->line_walker && *shell->line_walker != '\"' && *shell->line_walker != '\'' && *shell->line_walker != ' ')
		{
			printf("line walker:%s\n", shell->line_walker);
			shell->line_walker++;
			size_command++;
		}
		if (quotes)
			shell->line_walker++;
		//printf("start_command: %s\n", start_command);
		printf("size_command: %i\n", size_command);
		quotes = jump_quotes(shell);
		start_command = ft_substr(start_command, 0, size_command);
		//printf("start command:%s\n", start_command);
		printf("command:%s\n", command);
		command = ft_strjoin(command, start_command);
	}
	printf("command:%s\n", command);
	while (*shell->line_walker && *shell->line_walker != ' ')
	{
		size_command++;
		shell->line_walker++;
	}
	//printf("start command: %s\n", start_command);
	//printf("line walker: %s\n", shell->line_walker);
	while (i < shell->size_c && ft_strcmp(command, shell->list_commands[i]))
		i++;
	if (i >= shell->size_c)
		return (-1);
	printf("line walker:%s\n", shell->line_walker);
	if (!ft_strcmp(shell->list_commands[i], "echo")) //Comprueba la flag si el comando es "echo", este flag no se introduce en "shell->line_args" ni en "shell->line_walker"
		check_flag(shell);
	while (*shell->line_walker == ' ')
		shell->line_walker++;
	shell->line_args = shell->line_walker;
	shell->command = shell->list_commands[i];
	printf("line walkerthis:%s\n", shell->line_walker);
	return (0);
}

void add_arg(t_shell *shell, char *start_arg, int size_prev)
{
	t_arglist	*this_arg;

	if (size_prev > 0 && *start_arg)
	{
		start_arg = ft_substr(start_arg, 0, size_prev);
		this_arg = arg_node_new(start_arg);
		arglstadd_back(&shell->arg_list, this_arg);
	}
}

int	add_quotes_argument(t_shell *shell, char *start_arg, int size_prev)
{
	int 		i;
	t_arglist	*this_arg;
	char 		quotes;

	i = 0;
	//printf("line walker:%s\n", shell->line_walker);
	quotes = check_allquotes(shell->line_walker);
	if (check_quotes(shell->line_walker, quotes))
	{
		add_arg(shell, start_arg, size_prev);
		i = size_quotes_arg(shell->line_walker, quotes) + 2;
		start_arg = shell->line_walker;
		start_arg = ft_substr(start_arg, 0, i);
		if (*start_arg)
		{
			this_arg = arg_node_new(start_arg);
			if (ft_strcmp(start_arg, "\'\'") && ft_strcmp(start_arg, "\"\""))
				arglstadd_back(&shell->arg_list, this_arg);
			shell->line_walker += i;
		}
		return (1);
	}
	return (0);
}

int	add_space_argument(t_shell *shell, char *start_arg, int size_prev)
{
	if (*shell->line_walker == ' ')
	{
		add_arg(shell, start_arg, size_prev);
		shell->line_walker++;
		return (1);
	}
	return (0);
}

int argument_list_creator(t_shell *shell)
{
    int         size_prev; //Contamos para luego dividir con substr
    char        *start_arg;

    size_prev = 0;
    start_arg = shell->line_walker;
    while (*(shell->line_walker))
    {
        if (add_quotes_argument(shell, start_arg, size_prev)
			|| add_space_argument(shell, start_arg, size_prev))
        {
            if (!(*(shell->line_walker)))
                return (0);
            return (1);
        }
        shell->line_walker++;
        size_prev++;
    }
    if (!(*(shell->line_walker))) //Añade el ultimo argumento a la lista y devuelve 0 para que pare el bucle que llama a esta funcion
    {
		add_arg(shell, start_arg, size_prev);
        return (0);
    }
    shell->line_walker++;
    return (1);
}

int	split_arguments(t_shell *shell)
{
	int	count_args;
	t_arglist *printer;
	count_args = 0;

	printer = NULL;
	while (argument_list_creator(shell))
		count_args++;
	printer = shell->arg_list;
	//	AQUI VA TU FUNCION PASANDO POR LA LISTA ALBERTO, LA LISTA TIENE YA LAS COMILLAS INCLUIDAS EN CADA ARGUMENTO.
	shell->line_walker = shell->line_args;
	while (shell->arg_list)
	{
		printf("\nlinewalker: %s\n", shell->line_walker);
		printf("\ncheck_quotes: %c\n", check_allquotes(shell->line_walker));
		if (check_allquotes(shell->line_walker) != '\'')
			shell->arg_list->content= change_dollars(shell, shell->arg_list->content);
		shell->arg_list = shell->arg_list->next;
	}



	while (printer)
	{
		printf("Argument: %s\n", printer->content);
		printer = printer->next;
	}
	return (0);
}
