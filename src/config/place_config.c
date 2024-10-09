/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conf_and.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:12:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 06:51:12 by adherrer         ###   ########.fr       */
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

t_handler	*place_uniq_cmd(t_handler *a, int i)
{
	if ((a->state[0] == 6 || a->state[0] == 0) \
	&& a->state[1] == 14 && a->state[2] == 0)
		if (do_exec(a->info->tokens[i - 1], a->env))
			a->state[1] = UNIQ_COMMAND;
	return (a);
}

t_handler	*place_priority(t_handler *a)
{
	if (a->state[2] == 9 || a->state[2] == 10)
		a->block[a->info->i].priority = ((a->state[2] = 0), 1);
	return (a);
}
