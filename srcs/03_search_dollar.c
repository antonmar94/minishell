/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_search_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:28:58 by albzamor          #+#    #+#             */
/*   Updated: 2022/06/03 16:48:14 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	replace_content_runaway(t_aux_p *p)
{
	p->line_predolar = ft_substr(p->org_line_arg, 0, p->size_predollar);
	if (p->new_expanded)
	{
		p->line_predolar_joined = ft_strjoin(p->new_expanded, p->line_predolar);
		new_free(&p->new_expanded);
	}
	else
		p->line_predolar_joined = ft_strdup(p->line_predolar);
	p->new_expanded = ft_strjoin(p->line_predolar_joined, p->content);
	p->org_line_arg = p->org_line_arg + p->size_predollar + p->size_arg + 1;
	p->size_predollar = 0;
	p->line_walker += p->size_arg;
	if (p->new_expanded)
		free(p->new_expanded);
	p->new_expanded = ft_strjoin(p->line_predolar_joined, p->content);
}

void	nocontent_runaway(t_aux_p *p)
{
	p->line_predolar = ft_substr(p->org_line_arg, 0, p->size_predollar);
	if (p->new_expanded)
	{
		p->line_predolar_joined = ft_strjoin(p->new_expanded, p->line_predolar);
		new_free(&p->new_expanded);
	}
	else
		p->line_predolar_joined = ft_strdup(p->line_predolar);
	p->new_expanded = ft_strdup(p->line_predolar_joined);
	p->org_line_arg = p->org_line_arg + p->size_predollar + p->size_arg + 1;
	p->size_predollar = 0;
	p->line_walker += p->size_arg;
}

/* change dollar to content */
char	*change_dollars(t_shell *shell, char *str_to_change_dollar)
{
	shell->aux_p->org_line_arg = str_to_change_dollar;
	shell->aux_p->size_predollar = 0;
	shell->aux_p->line_walker = str_to_change_dollar;
	while (shell->aux_p->line_walker && *(shell->aux_p->line_walker))
	{
		if (*shell->aux_p->line_walker != '$' || (*shell->aux_p->line_walker
				== '$' && (!shell->aux_p->line_walker[1]
					|| shell->aux_p->line_walker[1] == ' ')))
		{
			shell->aux_p->line_walker++;
			shell->aux_p->size_predollar++;
		}
		else
			replace_dollar(shell);
	}
	if (str_to_change_dollar && (int)ft_strlen(str_to_change_dollar)
		== shell->aux_p->size_predollar)
		return (str_to_change_dollar);
	if (shell->aux_p->size_predollar)
		shell->aux_p->final_str = ft_strjoin(shell->aux_p->new_expanded,
				shell->aux_p->org_line_arg);
	else
		shell->aux_p->final_str = ft_strdup(shell->aux_p->new_expanded);
	new_free(&shell->aux_p->new_expanded);
	return (shell->aux_p->final_str);
}

void	replace_dollar(t_shell *shell)
{
	char	*first;

	shell->aux_p->line_walker++;
	first = ft_split_one(shell->aux_p->line_walker, ' ', '$');
	shell->aux_p->size_arg = ft_strlen(first);
	shell->aux_p->content = search_var_coincident(shell, first);
	if (shell->aux_p->content)
		replace_content_runaway(shell->aux_p);
	else
		nocontent_runaway(shell->aux_p);
	free(shell->aux_p->line_predolar);
	free(shell->aux_p->line_predolar_joined);
	free(first);
}