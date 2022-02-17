/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1d_search_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:28:58 by albzamor          #+#    #+#             */
/*   Updated: 2022/02/17 01:10:09 by albzamor         ###   ########.fr       */
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


void replace_content_runaway(t_aux_pointer *pointer)
{
	/* if(pointer->last_pos_until$)
		pointer->origin_line_arg --; */
	//pointer->line_until$=NULL;
	// se hace una substring de la original desde la ultima posicion antes de $ y el nº de caracteres avanzado
	int pos_new_$;

	pos_new_$ = 0;

	//if(pointer->line_until$_joined)
		//pos_new_$ += ft_strlen(pointer->line_until$_joined);

	printf("\norigin_line_arg:%s\n" ,pointer->origin_line_arg);
	pointer->line_until$ = ft_substr(pointer->origin_line_arg, 0, pointer->count_until$);
	printf("\nline_until$:%s\n" ,pointer->line_until$);
	printf("\nsize line_until$:%lu", ft_strlen(pointer->line_until$));
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
	
	//printf("\nline_until$_joined:%s\n" ,pointer->line_until$_joined);
	//Se avanzan los punteros para saltar las variables expandidas
	pointer->new_expanded_str =ft_strjoin(pointer->line_until$_joined, pointer->content);
	
	printf("unido contenido: pointer->new_expanded_str\n");
	printf(GREEN"%s\n"RESET, pointer->new_expanded_str);
	pointer->origin_line_arg = pointer->origin_line_arg + pointer->count_until$ + pointer->size_arg + 1;
	//pointer->last_pos_until$+=pointer->size_arg;
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
	t_aux_pointer *pointer;
	pointer = malloc(sizeof(t_aux_pointer));
	pointer->begin$ = NULL;

	pointer->origin_line_arg = shell->line;
	pointer->last_pos_until$ = 0;
	pointer->count_until$ = 0;
	pointer->new_expanded_str = NULL;

	int i = 0;


	check_envar(shell);//TODO: seguridad comprobacion variables entorno
	printf(YELLOW"fake arguments:\n"RESET);//TODO Del Test
	printf(RED"%s\n"RESET, shell->line);//TODO Del Test
	//printf("fake arguments expanded: ");//TODO Del Test

	pointer->shell_line_walker = shell->line;

	while (pointer->shell_line_walker && *(pointer->shell_line_walker))
	{
		if (*pointer->shell_line_walker != '$')
		{
			pointer->shell_line_walker++;
			pointer->count_until$++;
		}
		else
		{
			pointer->shell_line_walker++;
			pointer->first_$_found = ft_split_one(pointer->shell_line_walker, ' ');
			printf(WHITE"\n %i first$_found: %s\n"RESET, ++i, pointer->first_$_found);
			pointer->size_arg = ft_strlen(pointer->first_$_found);
			printf(CYAN"\nsize first$_found: %d\n"RESET, pointer->size_arg);
			//printf("\n000000000000");
			//if(!first_$_found)
				//return(0);
			pointer->content= search_var_coincident(shell, pointer->first_$_found);
			//exit(0);
			printf(CYAN"\ncontent: %s\n"RESET, pointer->content);
			if (pointer->content)
			{
				printf(CYAN"\nExiste Coincidencia pointer->content ✅ \n");

				replace_content_runaway(pointer);
				pointer->shell_line_walker+=pointer->size_arg;
				printf("\nline_until$: %s\n"RESET, pointer->line_until$);
				pointer->new_expanded_str =ft_strjoin(pointer->line_until$_joined, pointer->content);

			}
			else
			{
				exit(0);
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

