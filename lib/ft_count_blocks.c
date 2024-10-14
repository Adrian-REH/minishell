/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:11:16 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 06:28:21 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/headers/minishell.h"

void	count_blocks(t_handler *s)
{
	int	i;

	i = -1;
	while (s->info->tokens[++i])
	{
		if (idstr(s->operators, s->info->tokens[i]) == 8)
		{
			s->len_block++;
		}
		else if (idstr(s->operators, s->info->tokens[i]) == 7)
		{
			s->len_block++;
		}
	}
}
