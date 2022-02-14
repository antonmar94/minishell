/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1d_search_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:28:58 by albzamor          #+#    #+#             */
/*   Updated: 2022/02/14 23:07:54 by albzamor         ###   ########.fr       */
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


char *replace_content_runaway(char *line, int count_until$, int arg_size, char *content)
{
	char *line_until$;
	/* if(pointer->last_pos_until$)
		pointer->origin_line_arg --; */
	//pointer->line_until$=NULL;
	// se hace una substring de la original desde la ultima posicion antes de $ y el nº de caracteres avanzado
	line_until$ = ft_substr(line, count_until$, arg_size);

	//si anteriormente ya hay algo se concatena a lo anterior
	if(pointer->new_expanded_str)
	{
		//printf("\nline_until$: %s\n", pointer->line_until$);
		//printf("\nfirst$_found; %s\n", pointer->first_$_found);
		pointer->line_until$_joined = ft_strjoin(pointer->new_expanded_str, pointer->line_until$);
		free(pointer->new_expanded_str);
		pointer->new_expanded_str = NULL;
	}
	else// si anteriormente no hay nada es directamente lo anterior
	{
		pointer->line_until$_joined = pointer->line_until$;///AQQQUUUQQQQQ
		//printf("\nline_until$: %s\n", pointer->line_until$);
		//printf("\nfirst$_found; %s\n", pointer->first_$_found);
	}	

	//Se avanzan los punteros para saltar las variables expandidas
	pointer->origin_line_arg += pointer->size_arg  + ft_strlen(pointer->line_until$) -1;//var name + char $
	//se une lo anterior al contenido de la variable
	pointer->new_expanded_str =ft_strjoin(pointer->line_until$_joined, pointer->content);
	pointer->last_pos_until$+=pointer->size_arg;
	pointer->count_until$ = 0;
}


void	nocontent_runaway(t_aux_pointer *pointer)
{
	if(pointer->last_pos_until$)
		pointer->origin_line_arg --;

	pointer->line_until$ = ft_substr(pointer->origin_line_arg, pointer->last_pos_until$, pointer->count_until$);

	if(pointer->new_expanded_str)
	{
		pointer->line_until$_joined = ft_strjoin(pointer->new_expanded_str, pointer->line_until$);
		//free(pointer->new_expanded_str);
	}
	else
		pointer->line_until$_joined = pointer->line_until$;
		//printf("\nline_until$: %s\n", pointer->line_until$);
		//printf("\nfirst$_found; %s\n", pointer->first_$_found);
	pointer->origin_line_arg += pointer->size_arg  + ft_strlen(pointer->line_until$) -1;//var name + char $
	pointer->new_expanded_str =ft_strdup(pointer->line_until$_joined);
	pointer->last_pos_until$+=pointer->size_arg;
	pointer->count_until$ = 0;

	//new_expanded_str = line_until$_joined; //REVISAR
}


/* Utiliza shell->line_args que no tiene comando y cambia $ por contenido*/
char *change_dollars(t_shell *shell)
{
	/* t_aux_pointer *pointer;
	pointer = malloc(sizeof(t_aux_pointer));
	pointer->begin$ = NULL;

	pointer->origin_line_arg = shell->line;
	pointer->last_pos_until$ = 0;
	pointer->count_until$ = 0; */

	char 	*shell_line_walker;
	int		count_until$;
	char	*first_$_found;
	char	*last_pos_until$;
	char	*content = NULL;
	int		size_arg;

	printf("fake arguments         : ");//TODO Del Test
	printf(RED"%s\n"RESET, shell->line);//TODO Del Test
	//printf("fake arguments expanded: ");//TODO Del Test

	shell_line_walker = shell->line;

	while (shell_line_walker && *(shell_line_walker))
	{
		if (*shell_line_walker != '$')
		{
			shell_line_walker++;
			count_until$++;
		}
		else
		{
			shell->line++;
			first_$_found = ft_split_one(shell->line, ' ');
			//printf("\n000000000000");
			//if(!first_$_found)
				//return(0);
			printf("\nfirst$_found; %s\n", first_$_found);
			content = search_var_coincident(shell, first_$_found);
			size_arg = ft_strlen(first_$_found);
			//printf("\ncontent: %s\n", pointer->content);
			if (content)
			{
				//printf("\n11111111111111");
				replace_content_runaway(shell->line, count_until$, size_arg, content);
				shell->line+=pointer->size_arg;
				printf("\nline_until$: %s\n", pointer->line_until$);
				pointer->new_expanded_str =ft_strjoin(pointer->line_until$_joined, pointer->content);

			}
			else
			{
				nocontent_runaway(pointer);
				//shell->line+=pointer->size_arg;
				pointer->new_expanded_str =ft_strdup(pointer->line_until$_joined);
				printf("\n tam arg%d",pointer->size_arg);
				shell->line+=pointer->size_arg +1;
				//shell->line+=size_arg;
			}
				//printf("\n0000000001111");
		/* 	if (pointer->line_until$)
			{
				free(pointer->line_until$);
				pointer->line_until$ = NULL;
			} */

		}

	}
	//printf("\n2222222222");
	if (!pointer->begin$)
		return(pointer->origin_line_arg);


	//printf("\norigin_line :%s",pointer->origin_line_arg);
	//printf("\nlast_pos_until$ %d",pointer->last_pos_until$);
	//printf("\ncount_until$ :%d\n",pointer->count_until$);
	//printf("\npointer->final_without$ :%s\n",pointer->final_without$);
	//printf("\npointer->new_expanded_str :%s\n",pointer->new_expanded_str);

	pointer->final_without$ = ft_substr(pointer->origin_line_arg, pointer->last_pos_until$ -1, pointer->count_until$);
	pointer->final_return = ft_strjoin(pointer->new_expanded_str, pointer->final_without$);
	//printf("que pasa");

	//printf("\nline_until$_joined: %s\n", new_expanded_str);
	//printf("\nnew_expanded_strt$: %s\n", new_expanded_str );
	//printf("\nFinal final_without$: %s\n", final_without$ );
	//printf(GREEN"\n\n\nFinal RETURN$: %s\n"RESET, final_return );
	return(pointer->final_return);
	//t_arglist	*copy;
}

