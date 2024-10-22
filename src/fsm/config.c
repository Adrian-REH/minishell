/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:12:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/24 18:08:35 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	*handler_execute(t_handler *a)
{
	int		i;
	t_exec	*exec;
	int		i_exec;

	i = -1;
	while (a->info->tokens[++i])
	{
		a->state[2] = idstr(a->operators, a->info->tokens[i]);
		a = place_priority(a);
		a = place_uniq_cmd(a, i);
		exec = place_exec(a, exec, &i_exec);
		if (a->fta[a->state[0]][a->state[1]][a->state[2]])
		{
			a->fta[a->state[0]][a->state[1]][a->state[2]](a, i - 1);
			if (a->state[1] == OP_AND || a->state[1] == OP_OR)
				a->state[1] = 0;
		}
		a->block[a->info->i].len_exec++;
		a->state[1] = ((a->state[0] = a->state[1]), a->state[2]);
	}
	return (a->state);
}

int	init_config(t_handler *s)
{
	count_blocks(s);
	s->block = ft_calloc(sizeof(t_block), (s->len_block));
	if (!s->block)
		return (-1);
	s->info->oid = 30;
	if (pipe(s->block->fd) == -1)
		return (-1);
	s->block[s->info->i].op = BLOCK_EMPTY;
	s->block[s->info->i].isnext = 0;
	s->block[s->info->i].len_exec_prev = 0;
	s->block[s->info->i].len_exec_next = 0;
	s->block[s->info->i].len_exec = 0;
	s->block[s->info->i].prev_exec = 0;
	s->block[s->info->i].next_exec = 0;
	s->block[s->info->i].status = 0;
	return (0);
}

t_handler	*ft_config(t_handler *s)
{
	int	i;

	if (get_error() == 2 || get_error() == 1)
		return (s);
	s->state[0] = 0;
	s->state[1] = 0;
	s->state[2] = 0;
	s->info->i = 0;
	s->len_block = 1;
	if (init_config(s) < 0)
		return (NULL);
	handler_execute(s);
	i = 0;
	if (s->w_cmd)
	{
		while (s->w_cmd[i].pid)
			i++;
		s->n_pids = i;
	}
	return (s);
}
