/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:12:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/25 15:46:41 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static int	evaluate(t_automata *a)
{
	a->ostate = 0;
	a->i = -1;
	while (++a->i < ft_strlen(a->str) && a->state != 11)
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

static int	verify_syntax(t_handler *s)
{
	char	**tkn;
	int		state[3];

	state[0] = 0;
	state[1] = 0;
	state[2] = 0;
	tkn = s->info->tokens;
	while (*tkn)
	{
		state[2] = idstr(s->operators, *tkn);
		if (ft_strcmp(*tkn, "*") == 0)
			state[2] = OP_WILDCARD;
		if (s->ferror[state[0]][state[1]][state[2]])
			return (s->ferror[state[0]][state[1]][state[2]]("", 2));
		state[0] = state[1];
		state[1] = state[2];
		(tkn)++;
	}
	return (0);
}

void	automata_init(t_automata *a, void *data)
{
	alphabet_init(a);
	errors_init(a);
	tactions_init(a);
	a->data = data;
	a->get_state = get_state;
}

void	ft_handler_error(t_handler *s)
{
	int	code;

	code = 0;
	s->code = get_error();
	code = verify_syntax(s);
	if (code != 2 && code != 1)
		save_error(0);
	else
		s->code = get_error();
}

t_handler	*ft_parser(t_handler *s)
{
	int			finalstate;

	s->a = (t_automata *)ft_calloc(1, sizeof(t_automata));
	if (!s->a)
		return (NULL);
	s->info = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!s->info)
		return (NULL);
	s->info->i = 0;
	automata_init(s->a, s->info);
	s->a->str = s->line;
	finalstate = evaluate(s->a);
	if (finalstate > 11)
		get_token(s->a, s->info);
	if (finalstate >= 4 && finalstate <= 11)
		return (parser_error(s, finalstate - 4), s);
	s->info->tokens = ft_sarradd(s->info->tokens, " ");
	s->info->len_tokens = ft_sarrsize(s->info->tokens);
	(split_tokens(s), move_tokens(s), joins_tokens(s));
	ft_handler_error(s);
	ft_expand_tokens(s);
	return (s);
}
