/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conf_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:12:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 08:04:22 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	ft_setup_exec(t_exec *exec, t_handler *s)
{
	exec->handler = s;
	exec->cmd = ft_calloc(sizeof(t_cmd), 3);
	exec->op = PIPE;
	exec->cmd->handler = s;
	exec->state = ft_calloc(sizeof(int), 2);
	exec->state[0] = 0;
	exec->state[1] = 0;
	exec->cmd[0].cmd = 0;
	exec->file.input = 0;
	exec->file.output = 1;
}

static int	init_cmd(t_cmd *cmd, t_handler *s, int i, int k)
{
	if (s->info->oid != (i + k))
	{
		if (k == 1 && !strcmp(s->info->tokens[i + k], " "))
			return (1);
		cmd->line = s->info->tokens[i + k];
		cmd->pid = 0;
		cmd->status = 0;
		cmd->cmd = do_exec(s->info->tokens[i + k], s->env);
		cmd->cmd = sarr_clean_quote(cmd->cmd);
	}
	else
		return (1);
	return (0);
}

void	ft_conf_pipe(t_handler *s, int i)
{
	int		k;
	t_exec	*exec;
	t_block	*b;

	b = &(s->block[s->info->i]);
	if (s->block[s->info->i].isnext)
		exec = ((k = b->len_exec_next), b->next_exec);
	else
		exec = ((k = b->len_exec_prev), b->prev_exec);
	ft_setup_exec(exec + k, s);
	exec[k].state[0] = init_cmd(exec[k].cmd, s, i, -1);
	pipe(exec[k].cmd[0].fd_aux);
	exec[k].state[1] = init_cmd(exec[k].cmd + 1, s, i, 1);
	exec[k].cmd[2].cmd = NULL;
	exec[k].func[EMPTY][EMPTY] = ft_exec_pipe;
	s->info->oid = i + 1;
	if (s->block[s->info->i].isnext)
		b->len_exec_next++;
	else
		b->len_exec_prev++;
}
