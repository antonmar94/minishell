/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1d_search_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:28:58 by albzamor          #+#    #+#             */
/*   Updated: 2022/02/08 14:50:35 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *search_var_coincident(t_shell *shell, char* str_to_find)
{


	t_env_list *copy;
	copy = shell->env_list;

	while (copy->next)
	{
		if (ft_strcmp(copy->var_name, str_to_find))
			return(shell->env_list->var_content);
		copy = copy->next;
	}
	if (ft_strcmp(copy->var_name, str_to_find))
			return(shell->env_list->var_content);

	printf("no hay nada");
	return(0);

}

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
	int 	last_pos;
	int		size_arg;
	char *trozo;

	origin_line_arg = shell->line_args;
	last_pos = 0;
	printf("\nhola\n");
	printf("\nfake arguments: %s\n\n", shell->line_args);


	while (shell->line_args && *(shell->line_args))
	{
		if (*shell->line_args != '$')
			shell->line_args++;
		else
		{
			shell->line_args++;
			begin$ = shell->line_args;
			first_$_found = ft_split_one(begin$, ' ');
			size_arg = ft_strlen(first_$_found);
			if (search_var_coincident(shell, first_$_found) !=0)
			{
				trozo =ft_strjoin(ft_substr(shell->line_args, last_pos, last_pos + size_arg), first_$_found);
				last_pos +=size_arg;
				printf("trozo %s", trozo);
			}
			printf("\nprimera$: %s\n", first_$_found);
			//printf("\nsize primera %d:\n", size_arg);
			shell->line_args+=size_arg;
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