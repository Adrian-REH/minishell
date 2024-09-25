/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:11:16 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/25 15:46:11 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/headers/minishell.h"

static int	ft_isjoinedtoken(int state[3], char	**tokens, int *i, int y)
{
	char	*temp;

	if ((state[0] >= 1 && state[0] < 5) && state[1] == 14 && \
	state[2] == 14 && y != -1)
	{
		temp = tokens[y - 1];
		tokens[y - 1] = ft_strjoin(tokens[y - 1], " ");
		temp = (free(temp), tokens[y - 1]);
		tokens[y - 1] = ft_strjoin(tokens[y - 1], tokens[*i]);
		tokens = (free(temp), ft_sarrdelbyindex(tokens, *i));
		(*i)--;
		return (1);
	}
	return (0);
}

static int	ft_ismovedtoken(int state[3], char **tokens, int *i, int *pos[2])
{
	if ((state[0] >= 1 && state[0] < 5) && state[1] == 14 && \
	state[2] == 14 && *pos[0] != -1)
	{
		tokens = ft_sarraddbyindex(tokens, tokens[*i], *pos[0]);
		tokens = ft_sarrdelbyindex(tokens, *i + 1);
		(*i)--;
		*pos[1] = *pos[0] + 1;
		*pos[0] = -1;
		return (1);
	}
	return (0);
}

static int	isemptytoken(int state[3])
{
	return ((state[0] == OP_EMPTY || state[0] == OP_PIPE) && \
	(state[1] >= 1 && state[1] < 5) && state[2] == NOT_OPERATOR);
}

int	move_tokens(t_handler *s)
{
	int		i;
	int		j;
	int		y;
	char	**tokens;
	int		state[3];

	j = ((tokens = s->info->tokens), -1);
	state[0] = ((state[2] = 0), 0);
	i = ((state[1] = 0), -1);
	y = -1;
	while (tokens[++i])
	{
		state[2] = idstr(s->operators, tokens[i]);
		if (isemptytoken(state))
			j = i - 1;
		else if (ft_ismovedtoken(state, tokens, &i, (int *[2]){&j, &y}))
			i = i;
		else if (ft_isjoinedtoken(state, tokens, &i, y))
			i = i;
		state[1] = ((state[0] = state[1]), state[2]);
	}
	s->info->len_tokens = ft_sarrsize(tokens);
	s->info->tokens = tokens;
	return (1);
}
