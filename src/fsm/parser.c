/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:12:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 08:16:54 by adherrer         ###   ########.fr       */
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
		{
			a->fsa[a->state](a, a->data);
		}
		if (a->fta[a->ostate][a->state])
		{
			a->fta[a->ostate][a->state](a, a->data);
		}
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

void	ft_clean_tokens(t_handler *s)
{
	int		i;
	char	*space_pos;
	char	*quote_pos;
	char	*temp;
	char	**tokens;
	int		state[3];

	tokens = s->info->tokens;
	state[0] = 0;
	state[1] = 0;
	state[2] = 0;
	i = -1;
	while (tokens[++i])
	{
		state[2] = idstr(s->operators, tokens[i]);
		if (state[0] == 6 && state[2] == 14 && (state[1] >= 1 && state[1] < 5))
		{
			space_pos = ft_strchr(tokens[i], ' ');
			if (space_pos)
			{
				temp = tokens[i];
				tokens[i] = ft_substr(tokens[i], 0, ft_strlen(tokens[i]) - ft_strlen(space_pos));
				free(temp);
			}
		}
		else if (state[0] == 14 && (state[1] >= 1 && state[1] < 5) && state[2] == 14 && tokens[i])
		{
			space_pos = ft_strchr(tokens[i], ' ');
			if (tokens[i][0] == '\"' && space_pos)
			{
				temp = tokens[i - 2];
				quote_pos = ft_strchr(tokens[i] + 1, '\"');
				if (!quote_pos)
					continue;
				tokens[i - 2] = ft_strjoin(temp, quote_pos + 1);
				free(temp);
				temp = tokens[i];
				temp = ft_substr(temp + 1, 0, ft_strlen(tokens[i]) - ft_strlen(quote_pos) - 1);
				free(tokens[i]);
				tokens[i] = temp;
				tokens[i] = ft_strdelchr(tokens[i], '\"');
				continue;
			}
			if (space_pos)
			{
				temp = tokens[i - 2];
				tokens[i - 2] = ft_strjoin(temp, space_pos);
				free(temp);
				temp = tokens[i];
				tokens[i] = ft_substr(tokens[i], 0, ft_strlen(tokens[i]) - ft_strlen(space_pos));
				tokens[i] = ft_strdelchr(tokens[i], '\"');
				free(temp);
			}
		}
		state[0] = state[1];
		state[1] = state[2];
	}
}

t_handler	*ft_parser(t_handler *s)
{
	t_automata	a;
	t_data		info;
	int			finalstate;

	ft_bzero(&a, sizeof(t_automata));
	ft_bzero(&info, sizeof(t_data));
	automata_init(&a, &info);
	a.str = s->line;
	finalstate = evaluate(&a);
	if (finalstate > a.errorlen)
		get_token(&a, &info);
	info.tokens = ft_sarradd(info.tokens, " ");
	info.len_tokens = ft_sarrsize(info.tokens);
	s->info = &info;
	ft_clean_tokens(s);
	return (s);
}
