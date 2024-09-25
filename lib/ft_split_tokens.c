/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:11:25 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/25 15:44:55 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/headers/minishell.h"

int	split_tokens(t_handler *s)
{
	int		i;
	char	*space_pos;
	char	**tokens;
	int		state[3];

	tokens = s->info->tokens;
	state[0] = ((state[2] = 0), 0);
	i = ((state[1] = 0), -1);
	while (tokens[++i])
	{
		state[2] = idstr(s->operators, tokens[i]);
		space_pos = ft_strchr(tokens[i], ' ');
		if ((state[1] >= 1 && state[1] < 5) \
		&& state[2] == 14 && space_pos)
			tokens = split_token(tokens, space_pos, i++);
		state[1] = ((state[0] = state[1]), state[2]);
	}
	s->info->len_tokens = ft_sarrsize(tokens);
	s->info->tokens = tokens;

	return (1);
}

char	**split_token(char **tkn, char *space_pos, int i)
{
	char	*temp;
	char	*q_pos;

	if (tkn[i][0] == '\"' && space_pos)
	{
		q_pos = ft_strchr(tkn[i] + 1, '\"');
		temp = tkn[i];
		tkn[i] = ft_substr(tkn[i] + 1, 0, ft_strlen(tkn[i]) - ft_strlen(q_pos) - 1);
		if (!tkn[i])
			return (NULL);
		q_pos = ft_strtrim(q_pos, " ");
		tkn = ft_sarraddbyindex(tkn, q_pos, i + 1);
		tkn[i + 1] = (free(temp), ft_strdelchr(tkn[i + 1], '\"'));
	}
	else if (space_pos)
	{
		temp = tkn[i];
		tkn[i] = ft_substr(tkn[i], 0, ft_strlen(tkn[i]) - ft_strlen(space_pos));
		if (!tkn[i])
			return (NULL);
		space_pos = ft_strtrim(space_pos, " ");
		tkn = ft_sarraddbyindex(tkn, space_pos, i + 1);
		free(temp);
	}
	return (tkn);
}
