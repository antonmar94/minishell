/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   22_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albzamor <albzamor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 12:16:16 by albzamor          #+#    #+#             */
/*   Updated: 2022/05/08 12:20:57 by albzamor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint_handler(void)
{
	printf(BLUE"\nAlicornioPrompt$ "RESET);
}