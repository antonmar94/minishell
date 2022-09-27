/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliar_comp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 16:19:34 by albzamor          #+#    #+#             */
/*   Updated: 2022/09/27 02:17:34 by albzamor         ###   ########.fr       */
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

t_env_list *copy_list(t_env_list *env_list)
{
	t_env_list	*copy;
	t_env_list	*copy2;
	t_env_list	*copy3;

	copy = env_list;
	copy2 = malloc(sizeof(t_env_list));
	copy2->var_name = ft_strdup(copy->var_name);
	copy2->var_content = ft_strdup(copy->var_content);
	copy2->next = NULL;
	copy3 = copy2;
	copy = copy->next;
	while (copy)
	{
		copy2 = malloc(sizeof(t_env_list));
		copy2->var_name = ft_strdup(copy->var_name);
		copy2->var_content = ft_strdup(copy->var_content);
		copy2->next = NULL;
		copy3->next = copy2;
		copy3 = copy2;
		copy = copy->next;
	}
	return (copy2);
}

int	env_export(t_shell *shell)
{
	t_env_list *ordered_env_list;
	//t_env_list *copy_env_list;


	if (*shell->command_args)
		error_too_many_args(shell);

	//copy_env_list = copy_list(shell->env_list);
	ordered_env_list = order_env_list(shell->env_list);
	print_env_list_export(ordered_env_list);
	//free_env_list(ordered_env_list);
	return (0);
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
