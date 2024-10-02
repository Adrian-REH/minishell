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

static int	ft_isjoinedtoken(int state[3], t_data *info, int *i, int y)
{
	char	*temp;

	if ((state[0] >= 1 && state[0] < 5) && state[1] == 14 && \
	state[2] == 14 && y != -1)
	{
		temp = info->tokens[y - 1];
		info->tokens[y - 1] = ft_strjoin(info->tokens[y - 1], " ");
		temp = (free(temp), info->tokens[y - 1]);
		info->tokens[y - 1] = ft_strjoin(info->tokens[y - 1], info->tokens[*i]);
		info->tokens = (free(temp), ft_sarrdelbyindex(info->tokens, *i));
		(*i)--;
		return (1);
	}
	return (0);
}

static int	ft_ismovedtoken(int state[3], t_data *info, int *i, int **pos)
{
	if ((state[0] >= 1 && state[0] < 5) && state[1] == 14 && \
	state[2] == 14 && *pos[0] != -1)
	{
		info->tokens = ft_sarraddbyindex(info->tokens, \
		info->tokens[*i], *pos[0]);
		info->tokens = ft_sarrdelbyindex(info->tokens, *i + 1);
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
		else if (ft_ismovedtoken(state, s->info, &i, (int *[]){&j, &y}))
			i = i;
		else if (ft_isjoinedtoken(state, s->info, &i, y))
			i = i;
		state[1] = ((state[0] = state[1]), state[2]);
	}
	s->info->len_tokens = ft_sarrsize(s->info->tokens);
	return (1);
}
