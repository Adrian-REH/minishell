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

t_exec	*select_exec_block(t_block *b, int isnext)
{
	if (isnext)
	{
		b->len_exec = b->len_exec_next;
		return (b->next_exec);
	}
	else
	{
		b->len_exec = b->len_exec_prev;
		return (b->prev_exec);
	}
	return (NULL);
}

int	execute_cmds(t_block *b, int isnext)
{
	int		i;
	int		j;
	t_exec	*exec;

	j = ((i = -1), 0);
	exec = select_exec_block(b, isnext);
	while (++i < b->len_exec && get_error() == 0)
	{
		if (exec[i].func[0][0])
		{
			j += (setup_exec_io(j, i, b, exec), 1);
			if (exec[i].func[EMPTY][EMPTY])
				exec[i].state = exec[i].func[EMPTY][EMPTY](exec, i);
		}
	}
	return (0);
}

int	ft_waiting_pid(t_exec *exec, int len)
{
	int	i;
	int	j;
	int	status;

	i = -1;
	status = 0;
	while (++i < len)
	{
		j = -1;
		while (++j < 2 && exec[i].cmd)
		{
			if (exec[i].cmd[j].pid)
			{
				waitpid(exec[i].cmd[j].pid, &status, 0);
				exec[i].status = WEXITSTATUS(status);
			}
		}
	}
	return (exec[len - 1].status);
}

int	execute_block_sequence(t_block	*b, int l_blk, int i)
{
	if (b[i].len_exec_prev)
	{
		if (i == 0 && st_blk(0, BLOCK_EMPTY, b[i].op))
			return (1);
		else if (i != 0 && st_blk(b[i - 1].status, b[i - 1].op, b[i].op))
			return (1);
		execute_cmds(&(b[i]), 0);
		b[i].status = ft_waiting_pid(b[i].prev_exec, b[i].len_exec_prev);
	}
	else
		b[i].status = b[i - 1].status;
	if (b[i].len_exec_next)
	{
		if (st_blk(b[i].status, b[i].op, b[i].op))
			return (1);
		execute_cmds(&(b[i]), 1);
		b[i].status = ft_waiting_pid(b[i].next_exec, b[i].len_exec_next);
		if (i == l_blk - 1 && st_blk(b[i].status, b[i].op, BLOCK_EMPTY))
			return (1);
		else if (i != l_blk - 1 && st_blk(b[i].status, b[i].op, b[i].op))
			return (1);
	}
	else
		b[i].status = b[i - 1].status;
	return (0);
}

t_handler	*ft_execute(t_handler *s)
{
	int	i;

	i = -1;
	if (get_error() == 2)
		return (s);
	if (s->len_block == 0)
		return (s);
	while (++i < s->len_block)
	{
		if (!s->block[i - 1].priority && s->block[i].priority && \
		s->block[i - 1].status)
		{
			if (s->block[i + 1].op)
				s->block[i].status = s->block[i - 1].status;
			continue ;
		}
		if (execute_block_sequence(s->block, s->len_block, i) == -1)
			continue ;
	}
	return ((s->code = s->block[i - 1].status), s);
}
