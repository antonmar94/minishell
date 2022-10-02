/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliar_comp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 16:19:34 by albzamor          #+#    #+#             */
/*   Updated: 2022/10/02 22:18:29 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_env_list(t_env_list *envp)
{
	t_env_list	*copy;
	int			i;

	i = 0;
	copy = envp;
	while (copy->next)
	{
		printf(BLUE"%s"RESET, copy->var_name);
		printf("=");
		printf(GREEN"%s"RESET, copy->var_content);
		printf("\n");
		copy = copy->next;
		i++;
	}
	i++;
	printf(BLUE"%s"RESET, copy->var_name);
	printf("=");
	printf(GREEN"%s"RESET, copy->var_content);
	printf("\n");
}

int	size_matriz(char **str)
{
	char	**aux;
	int		i;

	i = 0;
	aux = str;
	while (*aux)
	{
		aux ++;
		i++;
	}
	return (i);
}

void	print_env_list_export(t_env_list *envp)
{
	t_env_list	*copy;
	int			i;

	i = 0;
	copy = envp;
	while (copy->next)
	{
		printf("declare -x ");
		printf(BLUE"%s"RESET, copy->var_name);
		printf("=");
		printf(GREEN"\"%s\""RESET, copy->var_content);
		printf("\n");
		copy = copy->next;
		i++;
	}
	i++;
	printf("declare -x ");
	printf(BLUE"%s"RESET, copy->var_name);
	printf("=");
	printf(GREEN"\"%s\""RESET, copy->var_content);
	printf("\n");
}
