/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1b_search_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonmar <antonmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 19:13:39 by antonmar          #+#    #+#             */
/*   Updated: 2022/02/11 21:00:36 by antonmar         ###   ########.fr       */
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

void	check_flag(t_shell *shell) //Comprueba si existe la flag -n en echo y si existe la introduce en "shell->command_flag"
{
	char *aux;
	while (*shell->line_walker== ' ')
		shell->line_walker++;
	if (!ft_strncmp(shell->line_walker, "-n", 2))
	{
		aux = shell->line_walker;
		aux += 2;
		if (*aux == ' ' || !(*aux))
		{
			shell->command_flag = "-n";
			shell->line_walker+= 3;
			while (*shell->line_walker && *shell->line_walker == ' ')
				shell->line_walker++;
		}
	}
}

int	add_command(t_shell *shell)
{
	int i;
	char quotes;
	int size_command;
	char	*start_command;

	//printf("line walker a comprobar comillas %s\n", shell->line_walker);
	i = 0;
	size_command = 0;
	shell->line_walker = shell->line;
	//printf("siize_prev %i\n", size_prev);
	while (*shell->line_walker == ' ')
		shell->line_walker++;
	quotes = jump_quotes(shell);
	printf("start command %s\n", shell->line_walker);
	printf("quotes %c\n", quotes);
	start_command = shell->line_walker;
	if (quotes)
	{
		while (*shell->line_walker && *shell->line_walker != quotes)
		{
			shell->line_walker++;
			size_command++;
		}
	}
	while (*shell->line_walker && *shell->line_walker != ' ')
	{
		if (!quotes && !check_allquotes(shell->line_walker))
			size_command++;
		else
			jump_quotes(shell);
	}
	printf("start command %s\n", start_command);
	printf("siize_command %i\n", size_command);
	while (i < shell->size_c && ft_strncmp(start_command, shell->list_commands[i], size_command))
		i++;
	if (i >= shell->size_c)
	{
		printf("siize_prev %i\n", i);
		return (-1);
	}
	if (!ft_strcmp(shell->list_commands[i], "echo")) //Comprueba la flag si el comando es "echo", este flag no se introduce en "shell->line_args" ni en "shell->line_walker"
		check_flag(shell);
	while (*shell->line_walker== ' ')
		shell->line_walker++;
	shell->line_args = shell->line_walker;
	shell->command = shell->list_commands[i];
	return (0);
}


int	add_simple_quotes_argument(t_shell *shell, char *start_arg, int size_prev)
{
	int i;
	t_arglist	*this_arg;

	//printf("line walker a comprobar comillas %s\n", shell->line_walker);
	i = 0;
	//printf("siize_prev %i\n", size_prev);
	if (check_quotes(shell->line_walker, '\''))
	{
		if (size_prev > 0)
		{
			start_arg = ft_substr(start_arg, 0, size_prev);
			this_arg = arg_node_new(start_arg);
			arglstadd_back(&shell->arg_list, this_arg);
		}
		i = size_quotes_arg(shell->line_walker, '\'');
		shell->line_walker++;
		start_arg = shell->line_walker;
		start_arg = ft_substr(start_arg, 0, i);
		if (*start_arg)
		{
			this_arg = arg_node_new(start_arg);
			//printf("y esto: %s\n ", start_arg);
			arglstadd_back(&shell->arg_list, this_arg);
			shell->line_walker += i;
		}
		shell->line_walker++;
		return (1);
	}
	return (0);
}

int argument_list_creator(t_shell *shell)
{
    int         size_prev; //Contamos para luego dividir con substr
    t_arglist   *this_arg;
    char        *start_arg;
    //char *aux;
    size_prev = 0;
    start_arg = shell->line_walker;
    while (*(shell->line_walker))
    {
        if (add_simple_quotes_argument(shell, start_arg, size_prev))
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
        printf("y esto: %s\n ", start_arg);
        printf("size_prev: %i\n ", size_prev);
        if (size_prev > 0 && *start_arg)
        {
            start_arg = ft_substr(start_arg, 0, size_prev);
            this_arg = arg_node_new(start_arg);
            arglstadd_back(&shell->arg_list, this_arg);
        }
        return (0);
    }
    if (*shell->line_walker != '\'')
        size_prev++;
    shell->line_walker++;
    return (1);
}

int	split_arguments(t_shell *shell)
{
	int	count_args;
	t_arglist *printer;
	count_args = 0;

	shell->line_walker = shell->line_args;
	printer = NULL;
	while (argument_list_creator(shell))
		count_args++;
	printer = shell->arg_list;
	while (printer)
	{
		printf("Argument: %s\n", printer->content);
		printer = printer->next;
	}
	return (0);
}




/*int	line_without_command(t_shell *shell) //Introduce la linea de argumentos sin el comando en "shell->line_args" y "shell->line_walker", el comando es introducido en "shell->command"
{
	int		count_until_space;
	int		i;
	char 	*start_line;
	int		valid_doublequotes;
	int		valid_singlequotes;

	count_until_space = 0;
	valid_doublequotes = 0;
	valid_singlequotes = 0;
	i = 0;
	
	while (*shell->line_walker && *shell->line_walker != ' ')
	{
		count_until_space++;
		shell->line_walker++;
	}
	
	printf("count_until_space %i\n", count_until_space);
	while (i < shell->size_c && ft_strncmp(shell->line, shell->list_commands[i], count_until_space))
			i++;
	if (i >= shell->size_c)
		return (-1);
	
	if (!ft_strcmp(shell->list_commands[i], "echo")) //Comprueba la flag si el comando es "echo", este flag no se introduce en "shell->line_args" ni en "shell->line_walker"
		check_flag(shell);
	
	while (*shell->line_walker && *shell->line_walker == '\'')
	{
		if (valid_singlequotes <= 0)
		{
			printf("sale\n");
			return (-1);
		}
		shell->line_walker++;
		valid_singlequotes--;
	}
	
	while (*shell->line_walker && *shell->line_walker == '\"')
	{
		if (valid_doublequotes <= 0)
			return (-1);
		shell->line_walker++;
		valid_doublequotes--;
	}
	
	if ((valid_singlequotes > 0 && *shell->line_walker != '\'') || (valid_singlequotes > 0 && *shell->line_walker != '\"'))
		return (-1);
	while (*shell->line_walker== ' ')
		shell->line_walker++;
	
	shell->line_args = shell->line_walker;
	shell->command = shell->list_commands[i];
	printf("command %s\n", shell->command);
	return (0);
}*/




/*int	add_space_argument(t_shell *shell, char *start_arg, int size_prev)
{
	int i;
	t_arglist	*this_arg;

	i = check_quotes(shell, ' ');
	if (i)
	{
		start_arg = ft_substr(start_arg, 0, size_prev);
		this_arg = arg_node_new(start_arg);
		arglstadd_back(&shell->arg_list, this_arg);
		shell->line_walker++;
		start_arg = shell->line_walker;
		start_arg = ft_substr(start_arg, 0, i);
		this_arg = arg_node_new(start_arg);
		arglstadd_back(&shell->arg_list, this_arg);
		shell->line_walker += i + 1;
		return (1);
	}
	return (0);
}*/

/*int	add_double_quotes_argument(t_shell *shell, char *start_arg, int size_prev)
{
	int i;
	t_arglist	*this_arg;

	i = check_quotes(shell, '\"');
	if (i)
	{
		start_arg = ft_substr(start_arg, 0, size_prev);
		
		if (start_arg)
		{
			this_arg = arg_node_new(start_arg);
			
			arglstadd_back(&shell->arg_list, this_arg);
		}
		shell->line_walker++;
		start_arg = shell->line_walker;
		start_arg = ft_substr(start_arg, 0, i);
		this_arg = arg_node_new(start_arg);
		arglstadd_back(&shell->arg_list, this_arg);
		shell->line_walker += i + 1;
		return (1);
	}
	return (0);
}*/

/*
int	count_quotes(t_shell *shell)
{
	char	*quotes_finder;
	int		quotes_count;

	quotes_finder = shell->line_walker;
	quotes_count = 0;
	while (*quotes_finder)
	{
		if (*quotes_finder == '\"')
			quotes_count++;
		quotes_finder++;
	}
	return (quotes_count);
}

int	space_and_quotes(t_shell *shell) //Esta funcion es una mierda, debe ser arreglada para que devuelva lo que debe devolver wordcounter cuando no hay espacio junto con comillas
{
	int		space_words;
	int		quotes_count;
	char	*quotes_finder;
	char	space;

	quotes_count = count_quotes(shell);
	quotes_finder = shell->line_walker;
	space_words = ft_wordcount(quotes_finder, ' ');
	printf("world_count: %i", space_words);
	while (*quotes_finder && quotes_count > 1)
	{
		while (*quotes_finder && *quotes_finder != '\"')
		{
			space = *quotes_finder;
			quotes_finder++;
		}
		if (space != ' ')
			space_words++;
		quotes_finder ++;
		while (*quotes_finder && *quotes_finder != '\"')
			quotes_finder++;
		quotes_finder++;
		if (*quotes_finder != ' ')
			space_words++;
		quotes_count = count_quotes(shell);
	}
	return (space_words);
}

int	count_args(t_shell *shell)
{
	int		space_words;
	int		quotes_count;
	char	*quotes_finder;

	quotes_count = count_quotes(shell);
	quotes_finder = shell->line_walker;
	space_words = space_and_quotes(shell);
	printf("space_words: %i", space_words);
	while (*quotes_finder && quotes_count > 1)
	{
		while (*quotes_finder && *quotes_finder != '\"')
			quotes_finder++;
		quotes_finder ++;
		while (*quotes_finder && *quotes_finder != '\"')
		{
			if (*quotes_finder == ' ')
				space_words--;
			quotes_finder++;
		}
		quotes_finder++;
 		if (*quotes_finder && *quotes_finder != ' ')
			space_words++;
		quotes_count = count_quotes(shell);
	}
	return (space_words);
}

int	arg_listing(t_shell *shell) //Introduce los argumentos limpios en "shell->command_args"
{
	char	*aux;

	if (line_without_command(shell) == -1)
		return (-1);
	while (shell->line_walker)
	{
		aux = shell->line_walker;
		if (*shell->line_walker == '\"' || *shell->line_walker == '\'')
		{
			shell->line_walker++;
			while (*aux != '\"' || *aux == '\'')
				aux++;
			if (!(*aux))
				while(*shell->line_walker != ' ')  //introduce " y hasta el primer espacio como primer argumento(como si de un caracter cualquiera se tratara)
				{
					
				}
			else
				return (aux);  //introduce lo que se encuentra entre comillas como primer argumento(ignorando los espacios)
		}
			//Si no hay comillas introduce lo que haya hasta el siguiente espacio
		shell->line_walker++;
	}
	return (0);
} */