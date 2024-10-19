/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conf_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:12:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/23 01:32:21 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	init_conf(t_exec *exec, t_handler *s, int i)
{
	exec->state = ft_calloc(sizeof(int), 2);
	exec->state[0] = 0;
	exec->state[1] = 0;
	exec->cmd = (t_cmd *)ft_calloc(sizeof(t_cmd), 3);
	exec->cmd->handler = s;
	exec->cmd->line = s->info->tokens[i];
	exec->cmd->pid = 0;
	exec->cmd->status = 0;
	exec->file.input = 0;
	exec->file.output = 1;
	exec->op = UNIQ_COMMAND;
	exec->cmd->cmd = do_exec(exec->cmd->line, s->env);
	if (!exec->cmd->cmd)
		exec->state[0] = 1;
	//exec->cmd->cmd = sarr_clean_quote(exec->cmd->cmd);
}

void	ft_conf_cmd(t_handler *s, int i)
{
	int		k;
	t_exec	*exec;
	t_block	*b;

	b = &(s->block[s->info->i]);
	if (s->block[s->info->i].isnext)
		exec = ((k = b->len_exec_next), b->next_exec);
	else
		exec = ((k = b->len_exec_prev), b->prev_exec);
	init_conf(exec + k, s, i);
	s->info->oid = i;
	exec[k].func[0][0] = (int *(*)(void *, int))ft_exec_cmd;
	if (s->block[s->info->i].isnext)
		s->block[s->info->i].len_exec_next++;
	else
		s->block[s->info->i].len_exec_prev++;
}
