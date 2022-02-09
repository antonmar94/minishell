/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1d_search_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:28:58 by albzamor          #+#    #+#             */
/*   Updated: 2022/02/09 16:34:20 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* if found one return de var content */
char *search_var_coincident(t_shell *shell, char* str_to_find)
{


	t_env_list *copy;
	copy = shell->env_list;

	while (copy->next)
	{

		if (!ft_strcmp(copy->var_name, str_to_find))
			return(copy->var_content);
		copy = copy->next;
	}
	if (!ft_strcmp(copy->var_name, str_to_find))
			return(copy->var_content);
	return(0);

}

/* modified split to return de first str before a char */
char	*ft_split_one(char const *s, char c)

{
	char	*scopy;
	char	*pp;
	size_t	i;
	size_t	desplace;

	i = 0;
	if (s == NULL)
		return (NULL);
	desplace = 0;
	scopy = (char *)s;
	pp = (char *)malloc(sizeof(char *));
	if (pp == NULL)
		return (NULL);

		scopy = scopy + ft_desplace(scopy, c);
		pp = ft_substr((const char *)scopy, 0, ft_lens(scopy, c));
	return (pp);
}

/* Utiliza shell->line_args que no tiene comando y cambia $ por contenido*/
int	change_dollars(t_shell *shell)
{
	char *origin_line_arg;
	char	*begin$;
	char	*first_$_found;
	char	*line_until$_joined;
	int 	last_pos_until$;
	int		size_arg;
	int		count_until$;
	char *line_until$;
	char *new_expanded_str;
	char *content;

	origin_line_arg = shell->line;
	last_pos_until$ = 0;
	count_until$ = 0;
	printf("fake arguments: ");
	printf(RED"%s\n\n"RESET, shell->line);


	while (shell->line&& *(shell->line))
	{
		if (*shell->line != '$')
		{
			shell->line++;
			count_until$++;
		}

		else
		{
			shell->line++;
			begin$ = shell->line;
			first_$_found = ft_split_one(begin$, ' ');
			content = search_var_coincident(shell, first_$_found);
			size_arg = ft_strlen(first_$_found);
			printf("\ncontent: %s\n", content);
			if (content)
			{

				printf("count_until$%d", count_until$);
				line_until$ = ft_substr(origin_line_arg, last_pos_until$, count_until$ -1);
				if(new_expanded_str)
				{
					line_until$_joined = ft_strjoin(new_expanded_str, line_until$);
					free(new_expanded_str);
				}
				else
					line_until$_joined = line_until$;
				printf("\nline_until$: %s\n", line_until$);
				printf("\nfirst$_found; %s\n", first_$_found);
				origin_line_arg += size_arg + ft_strlen(line_until$) -1;//var name + char $
				new_expanded_str =ft_strjoin(line_until$_joined, content);
				free(line_until$);
				last_pos_until$+=size_arg;
				count_until$ = 0;
			}
			shell->line+=size_arg;
			printf("\nline_until$_joined: %s\n", new_expanded_str);
		}

	}

	//t_arglist	*copy;















	// no buscar en la lista de argumentos sino modificar la linea que
	// o hay ' ' fuertes y dejar la linea preparada sustituyendo los $ por el coontenido
	// de la variable env encontrada
	/* while (arg_list->next)
	{
		while (*arg_list->content != '$')
			arg_list->content++;
		arg_list->content++;
		if(search_var_coincident(env_list, ++arg_list->content))
			ft_strjoin()
		arg_list = arg_list->next;
	}
	while (*arg_list->content != '$')
			arg_list->content++;
		arg_list->content++;
		search_var_coincident(env_list, ++arg_list->content);
	return();
 */
	return(0);
}