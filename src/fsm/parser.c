/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:12:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/24 18:07:44 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static int	evaluate(t_automata *a)
{
	a->ostate = 0;
	a->i = -1;
	while (++a->i < ft_strlen(a->str))
	{
		a->state = a->get_state(a->state, idx(a->alphabet, a->str[a->i]));
		if (a->fsa[a->state])
			a->fsa[a->state](a, a->data);
		if (a->fta[a->ostate][a->state])
			a->fta[a->ostate][a->state](a, a->data);
		a->ostate = a->state;
	}
	return (a->state);
}

void	automata_init(t_automata *a, void *data)
{
	alphabet_init(a);
	errors_init(a);
	tactions_init(a);
	a->data = data;
	a->get_state = get_state;
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

int	move_tokens(t_handler *s)
{
	int		i;
	int		j;
	int		y;
	char	*temp;
	char	**tokens;
	int		state[3];

	j = ((tokens = s->info->tokens), -1);
	state[0] = ((state[2] = 0), 0);
	i = ((state[1] = 0), -1);
	y = -1;
	while (tokens[++i])
	{
		state[2] = idstr(s->operators, tokens[i]);
		if ((state[0] == 0 || state[0] == 6) && (state[1] >= 1 && state[1] < 5) && state[2] == 14)
			j = i - 1;
		else if ((state[0] >= 1 && state[0] < 5) && state[1] == 14  && state[2] == 14 && j != -1)
		{
			tokens = ft_sarraddbyindex(tokens, tokens[i], j);
			tokens = ft_sarrdelbyindex(tokens, i + 1);
			i--;
			y = j + 1;
			j = -1;
		}
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
		state[1] = ((state[0] = state[1]), state[2]);
	}
	s->info->len_tokens = ft_sarrsize(tokens);
	s->info->tokens = tokens;
	return (1);
}

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

t_handler	*ft_parser(t_handler *s)
{
	int			finalstate;
	t_automata	a;
	t_data		info;

	ft_bzero(&a, sizeof(t_automata));
	ft_bzero(&info, sizeof(t_data));
	s->a = &a;
	s->info = &info;
	automata_init(s->a, s->info);
	s->a->str = s->line;
	finalstate = evaluate(s->a);
	if (finalstate > s->a->errorlen)
		get_token(s->a, s->info);
	s->info->tokens = ft_sarradd(s->info->tokens, " ");
	s->info->len_tokens = ft_sarrsize(s->info->tokens);
	split_tokens(s);
	move_tokens(s);
	joins_tokens(s);
	return (s);
}
