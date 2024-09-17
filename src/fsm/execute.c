/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:12:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 06:22:21 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	execute_cmds(t_block *b, int isnext)
{
	int		i;
	int		j;
	t_exec	*exec;

	j = ((i = -1), 0);
	if (isnext)
		b->len_exec = ((exec = b->next_exec), b->len_exec_next);
	else
		b->len_exec = ((exec = b->prev_exec), b->len_exec_prev);
	while (++i < b->len_exec)
	{
		if (exec[i].func[0][0])
		{
			if ((j == b->len_exec - 1) && (exec[i].op == PIPE || exec[i].op == HEREDOC || exec[i].op == LESS))
			{
				exec[i].file.input = b->fd[0];
				exec[i].file.output = 1;
				if (exec[i].cmd[1].cmd)
					exec[i].cmd[1].towait = 1;
			}
			if (j < (b->len_exec) && j > 0 && (exec[i].op == PIPE || exec[i].op == GREATER || exec[i].op == LESS))
			{
				exec[i].file.input = b->fd[0];
				exec[i].file.output = (pipe(b->fd), b->fd[1]);
			}
			j++;
			if (j == 1 && 1 != b->len_exec && (exec[i].op == PIPE || exec[i + 1].op == PIPE || exec[i].op == LESS))
				exec[i].file.output = (b->fd[1]);
			else if (j == b->len_exec && (exec[i].op == PIPE || exec[i].op == HEREDOC || exec[i].op == LESS))
				exec[i].file.output = 1;
			exec[i].state = exec[i].func[EMPTY][EMPTY](exec, i);
		}
	}
	return (0);
}

int	status_block(int sts, int op, int next_op)
{
	int	status[3][2][3];

	status[BLOCK_EMPTY][0][BLOCK_EMPTY] = 0;
	status[BLOCK_EMPTY][0][BLOCK_AND] = 0;
	status[BLOCK_EMPTY][1][BLOCK_AND] = 1;
	status[BLOCK_EMPTY][0][BLOCK_OR] = 0;
	status[BLOCK_EMPTY][1][BLOCK_OR] = 1;
	status[BLOCK_OR][0][BLOCK_OR] = 1;
	status[BLOCK_OR][1][BLOCK_OR] = 1;
	status[BLOCK_OR][0][BLOCK_AND] = 0;
	status[BLOCK_OR][1][BLOCK_AND] = 1;
	status[BLOCK_AND][0][BLOCK_AND] = 0;
	status[BLOCK_AND][1][BLOCK_AND] = 1;
	status[BLOCK_AND][0][BLOCK_OR] = 1;
	status[BLOCK_AND][1][BLOCK_OR] = 0;
	status[BLOCK_AND][0][BLOCK_EMPTY] = 0;
	status[BLOCK_AND][1][BLOCK_EMPTY] = 1;
	status[BLOCK_OR][0][BLOCK_EMPTY] = 0;
	status[BLOCK_OR][1][BLOCK_EMPTY] = 1;
	return (status[op][sts][next_op]);
}

int	ft_waiting_pid(t_exec *exec, int len)
{
	int	i;
	int	status;

	i = -1;
	while (++i < len)
	{
		if (exec[i].cmd->pid)
		{
			waitpid(exec[i].cmd->pid, &status, 0);
			exec[i].status = WEXITSTATUS(status);
		}
	}
	return (exec[len - 1].status);
}

int	*block_execute(t_handler *s)
{
	int	i;

	i = -1;
	while (++i < s->len_block)
	{
		if (s->block[i].len_exec_prev)
		{
			if (i == 0 && status_block(0, BLOCK_EMPTY, s->block[i].op))
				continue ;
			else if (i != 0 && status_block(s->block[i - 1].status, s->block[i - 1].op, s->block[i].op))
				continue ;
			execute_cmds(&(s->block[i]), 0);
			s->block[i].status = ft_waiting_pid(s->block[i].prev_exec, s->block[i].len_exec_prev);
		}
		if (s->block[i].len_exec_next)
		{
			if (status_block(s->block[i].status, s->block[i].op, s->block[i].op))
				continue ;
			execute_cmds(&(s->block[i]), 1);
			s->block[i].status = ft_waiting_pid(s->block[i].next_exec, s->block[i].len_exec_next);
			if (i == s->len_block - 1 && status_block(s->block[i].status, s->block[i].op, BLOCK_EMPTY))
				continue ;
			else if (i != s->len_block - 1 && status_block(s->block[i].status, s->block[i].op, s->block[i].op))
				continue ;
		}
	}
	return ((s->code = s->block[i - 1].status), NULL);
}

t_handler	*ft_execute(t_handler *s)
{
	block_execute(s);
	return (s);
}
