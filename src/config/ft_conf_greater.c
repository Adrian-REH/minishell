/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conf_greater.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:12:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 08:25:39 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	init_conf(t_exec *exec, t_handler *s)
{
	exec->handler = s;
	exec->cmd = ft_calloc(sizeof(t_cmd), 3);
	exec->cmd->handler = s;
	exec->op = GREATER;
	exec->state = ft_calloc(sizeof(int), 2);
	exec->state[0] = 0;
	exec->state[1] = 0;
	exec->cmd[0].cmd = 0;
	exec->file.input = 0;
	exec->file.output = 1;
	exec->file.content = NULL;
}

static int	init_cmd(t_cmd *cmd, t_handler *s, int i, int k)
{
	if (s->info->oid != (i + k) && ft_strcmp(s->info->tokens[i + k], "|"))
	{
		cmd->line = s->info->tokens[i + k];
		cmd->cmd = do_exec(s->info->tokens[i + k], s->env);
		cmd->cmd = sarr_clean_quote(cmd->cmd);
		cmd->towait = 0;
		cmd->pid = 0;
		cmd->status = 0;
		pipe(cmd->fd_aux);
	}
	else
		return (1);
	return (0);
}

static int	init_file(t_exec *exec, t_handler *s, int i, int k)
{
	char	*line;

	if (s->info->oid != (i + k))
	{
		line = s->info->tokens[i + k];
		line = ft_strdelchr(line, '\"');
		exec->file.odfile = line;
	}
	else
		return (1);
	return (0);
}

static void	ft_move_conf(t_exec *exec, int k)
{
	int	j;

	j = k - 1;
	while (j >= 0 && exec[j].op != PIPE && exec[j].op != HEREDOC)
	{
		if (exec[j].state[0] == 0)
		{
			exec[k].cmd[0].line = exec[j].cmd[0].line;
			exec[j].cmd[0].line = NULL;
			if (exec[k].cmd->cmd)
				exec[k].cmd->cmd = (free(exec[k].cmd->cmd), NULL);
			exec[k].cmd[0].cmd = exec[j].cmd[0].cmd;
			exec[j].cmd[0].cmd = NULL;
			exec[k].cmd[0].fd_aux[0] = (exec[j].cmd[0].fd_aux[0]);
			exec[k].cmd[0].fd_aux[1] = (exec[j].cmd[0].fd_aux[1]);
			exec[k].state[0] = 0;
			exec[j].state[0] = 1;
		}
		j--;
	}
}

void	ft_conf_greater(t_handler *s, int i)
{
	int		k;
	t_exec	*exec;
	t_block	*b;

	b = &(s->block[s->info->i]);
	if (s->block[s->info->i].isnext)
		exec = ((k = b->len_exec_next), b->next_exec);
	else
		exec = ((k = b->len_exec_prev), b->prev_exec);
	init_conf(exec + k, s);
	exec[k].state[0] = init_cmd(exec[k].cmd, s, i, -1);
	exec[k].state[1] = init_file(&(exec[k]), s, i, 1);
	ft_move_conf(exec, k);
	s->info->oid = i + 1;
	exec[k].func[0][0] = (int *(*)(void *, int))ft_exec_greater;
	if (s->block[s->info->i].isnext)
		b->len_exec_next++;
	else
		b->len_exec_prev++;
}
// 