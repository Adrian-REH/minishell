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
	printf("PRIMERO SPLITEO LOS TOKENS\n");
	ft_sarrprint(s->info->tokens);
	move_tokens(s);
	printf("SEGUNDO MUEVO LOS TOKENS\n");
	ft_sarrprint(s->info->tokens);
	joins_tokens(s);
	printf("TERCERO UNO LOS TOKENS\n");
	ft_sarrprint(s->info->tokens);
	return (s);
}
