/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:11:22 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 06:28:19 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/headers/minishell.h"

void	get_token(t_automata *a, void *data)
{
	char	*cmdline;
	char	*aux;
	t_data	*info;

	info = (t_data *)data;
	cmdline = ft_substr(a->str, a->j, a->i - a->j);
	aux = cmdline;
	cmdline = ft_strtrim(cmdline, " ");
	free(aux);
	a->j = a->i;
	info->tokens = ft_sarradd(info->tokens, cmdline);
	free(cmdline);
}
