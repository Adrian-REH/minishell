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

t_exec	*place_exec(t_handler *a, t_exec *exec, int *i_exec)
{
	t_block	*b;

	b = &(a->block[a->info->i]);
	if (b->isnext)
	{
		b->next_exec = \
		ft_realloc(b->next_exec, sizeof(t_exec) * (b->len_exec_next + 1));
		exec = b->next_exec;
		*i_exec = b->len_exec_next;
	}
	else
	{
		b->prev_exec = \
		ft_realloc(b->prev_exec, sizeof(t_exec) * (b->len_exec_prev + 1));
		*i_exec = b->len_exec_prev;
		exec = b->prev_exec;
	}
	exec[*i_exec].handler = a;
	swap_lst_cmd(exec, *i_exec, a);
	return (exec);
}

int	*handler_execute(t_handler *a)
{
	int		i;
	int		j;
	t_exec	*exec;
	int		i_exec;

	j = ((i = -1), 0);
	while (a->info->tokens[++i])
	{
		a->state[2] = idstr(a->operators, a->info->tokens[i]);
		if (a->state[2] == 9 || a->state[2] == 10)
			a->block[a->info->i].priority = ((a->state[2] = 0), 1);
		if ((a->state[0] == 6 || a->state[0] == 0) && a->state[1] == 14 && a->state[2] == 0)
			if (do_exec(a->info->tokens[i - 1], a->env))
				a->state[1] = UNIQ_COMMAND;
		exec = place_exec(a, exec, &i_exec);
		if (a->fta[a->state[0]][a->state[1]][a->state[2]])
		{
			a->fta[a->state[0]][a->state[1]][a->state[2]](a, i - 1);
			if (a->state[1] == OP_AND || a->state[1] == OP_OR)
				a->state[1] = 0;
		}
		a->block[a->info->i].len_exec = ++j;
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

	if (get_error() == 2)
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
