/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1d_search_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:28:58 by albzamor          #+#    #+#             */
/*   Updated: 2022/02/17 13:17:36 by albzamor         ###   ########.fr       */
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


/**
 replace global var($) to his content
 @param line_until$ substring (malloc) filled with the chars advanceds count_until$
 @param new_expanded_str save the last piece of the string
 @param line_until$_joined
 @param content Comtent of the global var

 @param origin_line_arg the string to advance to obtain line_until$

*/
void replace_content_runaway(t_aux_pointer *pointer)
{
	printf("\norigin_line_arg:%s\n" ,pointer->origin_line_arg);//TODO del
	pointer->line_until$ = ft_substr(pointer->origin_line_arg, 0, pointer->count_until$);
	printf("\nline_until$:%s\n" ,pointer->line_until$);//TODO del
	printf("size line_until$: %lu\n", ft_strlen(pointer->line_until$));//TODO del
	//si anteriormente ya hay algo se concatena a lo anterior
	if(pointer->new_expanded_str)
		pointer->line_until$_joined = ft_strjoin(pointer->new_expanded_str, pointer->line_until$);
	else
		pointer->line_until$_joined = pointer->line_until$;
	pointer->new_expanded_str =ft_strjoin(pointer->line_until$_joined, pointer->content);
	printf("\nunido contenido: pointer->new_expanded_str\n");//TODO del
	printf(GREEN"%s\n"RESET, pointer->new_expanded_str);//TODO del
	printf(CYAN"size: %lu\n", ft_strlen(pointer->new_expanded_str));
	pointer->origin_line_arg = pointer->origin_line_arg + pointer->count_until$ + pointer->size_arg + 1;
	pointer->count_until$ = 0;
	if(pointer->first_$_found)
		free(pointer->first_$_found);
}


void	nocontent_runaway(t_aux_pointer *pointer)
{
	printf("\norigin_line_arg:%s\n" ,pointer->origin_line_arg);//TODO del
	pointer->line_until$ = ft_substr(pointer->origin_line_arg, 0, pointer->count_until$);
	printf("\nline_until$:%s\n" ,pointer->line_until$);//TODO del
	printf("size line_until$: %lu\n", ft_strlen(pointer->line_until$));//TODO del
	if(pointer->new_expanded_str)
		pointer->line_until$_joined = ft_strjoin(pointer->new_expanded_str, pointer->line_until$);
	else
		pointer->line_until$_joined = pointer->line_until$;
	pointer->new_expanded_str = pointer->line_until$_joined;
	printf("\nunido contenido: pointer->new_expanded_str\n");//TODO del
	printf(GREEN"%s\n"RESET, pointer->new_expanded_str);//TODO del
	printf("size: %lu\n", ft_strlen(pointer->new_expanded_str));
	pointer->origin_line_arg = pointer->origin_line_arg + pointer->count_until$ + pointer->size_arg + 1;
	pointer->count_until$ = 0;
	if(pointer->first_$_found)
		free(pointer->first_$_found);
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
				pointer->new_expanded_str =ft_strjoin(pointer->line_until$_joined, pointer->content);
			}
			else
			{
				printf(CYAN"\nNO Existe Coincidencia pointer->content ❌ \n");
				nocontent_runaway(pointer);
				pointer->shell_line_walker+=pointer->size_arg;
				shell->line+=pointer->size_arg +1;
				pointer->new_expanded_str = pointer->line_until$_joined;

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

