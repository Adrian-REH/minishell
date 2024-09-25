/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:11:16 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/25 15:46:57 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/headers/minishell.h"

int	joins_tokens(t_handler *s)
{
	int		i;
	int		y;
	char	*temp;
	char	**tokens;
	int		state[3];

	tokens = s->info->tokens;
	state[0] = ((state[2] = 0), 0);
	i = ((state[1] = 0), -1);
	y = -1;
	while (tokens[++i])
	{
		state[2] = idstr(s->operators, tokens[i]);
		if (state[0] == 14 && (state[1] >= 1 && state[1] < 5) && state[2] == 14 && y == -1)
			y = i - 1;
		else if ((state[0] >= 1 && state[0] < 5) && state[1] == 14  && state[2] == 14 && y != -1)
		{
			temp = tokens[y - 1];
			tokens[y - 1] = ft_strjoin(tokens[y - 1], " ");
			free(temp);
			temp = tokens[y - 1];
			tokens[y - 1] = ft_strjoin(tokens[y - 1], tokens[i]);
			free(temp);
			tokens = ft_sarrdelbyindex(tokens, i);
			i--;
		}
		if (state[1] == 6)
			y = -1;
		state[1] = ((state[0] = state[1]), state[2]);
	}
	s->info->len_tokens = ft_sarrsize(tokens);
	s->info->tokens = tokens;
	return (1);
}