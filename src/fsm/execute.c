/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:12:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/24 18:09:57 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	setup_exec_io(int j, int i, t_block *b, t_exec *exec)
{
	if ((j == b->len_exec - 1) && \
	(exec[i].op == PIPE || exec[i].op == HEREDOC || exec[i].op == LESS))
	{
		exec[i].file.input = b->fd[0];
		exec[i].file.output = 1;
		if (exec[i].cmd[1].cmd)
			exec[i].cmd[1].towait = 1;
	}
	if (j < (b->len_exec) && j > 0 && \
	(exec[i].op == 3 || exec[i].op == 7 || exec[i].op == 5 || exec[i].op == 6))
	{
		exec[i].file.input = b->fd[0];
		exec[i].file.output = (pipe(b->fd), b->fd[1]);
	}
}

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
	while (++i < b->len_exec && get_error(0) == 0)
	{
		if (exec[i].func[0][0])
		{
			j += (setup_exec_io(j, i, b, exec), 1);
			if (j == 1 && 1 != b->len_exec && \
			(exec[i].op == PIPE || exec[i + 1].op == PIPE || exec[i].op == 5))
				exec[i].file.output = (b->fd[1]);
			else if (j == b->len_exec && \
			(exec[i].op == PIPE || exec[i].op == HEREDOC || exec[i].op == LESS))
				exec[i].file.output = 1;
			if (exec[i].func[EMPTY][EMPTY])
				exec[i].state = exec[i].func[EMPTY][EMPTY](exec, i);
		}
	}
	return (0);
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

int	execute_block_sequence(t_handler *s, int i)
{
	t_block	*b;

	b = s->block;
	if (b[i].len_exec_prev)
	{
		if (i == 0 && st_blk(0, BLOCK_EMPTY, b[i].op))
			return (1);
		else if (i != 0 && st_blk(b[i - 1].status, b[i - 1].op, b[i].op))
			return (1);
		execute_cmds(&(b[i]), 0);
		b[i].status = ft_waiting_pid(b[i].prev_exec, b[i].len_exec_prev);
	}
	if (b[i].len_exec_next)
	{
		if (st_blk(b[i].status, b[i].op, b[i].op))
			return (1);
		execute_cmds(&(b[i]), 1);
		b[i].status = ft_waiting_pid(b[i].next_exec, b[i].len_exec_next);
		if (i == s->len_block - 1 && st_blk(b[i].status, b[i].op, BLOCK_EMPTY))
			return (1);
		else if (i != s->len_block - 1 && st_blk(b[i].status, b[i].op, b[i].op))
			return (1);
	}
	return (0);
}

t_handler	*ft_execute(t_handler *s)
{
	int	i;

	i = -1;
	while (++i < s->len_block)
	{
		if (execute_block_sequence(s, i) == -1)
			continue ;
	}
	return ((s->code = s->block[i - 1].status), s);
}
