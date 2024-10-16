/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_amper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:12:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 06:21:38 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include <sys/types.h>

static int	*ft_exec(t_exec *e)
{
	e->cmd->pid = fork();
	if (e->cmd->pid < 0)
		return (ft_print_error("fork", 1, ""), NULL);
	else if (e->cmd->pid == 0)
		exit(dispatch_command(e));
	return (NULL);
}

static void	ft_wait(t_exec *e)
{
	pid_t	result;

	result = waitpid(e->cmd->pid, &e->cmd->status, WNOHANG);
	if (result == 0)
	{
		e->handler->n_pids++;
		e->handler->w_cmd = add_cmd(e->handler->w_cmd, *(e->cmd));
		printf("[%d] %d\n", e->handler->n_pids, e->cmd->pid);
	}
	e->cmd->pid = 0;
}

int	*ft_exec_amper(t_exec *e, int index)
{
	e = &e[index];
	if (e->state[0] == 0)
	{
		ft_exec(e);
		ft_wait(e);
	}
	e->cmd++;
	if (e->state[1] == 0 && e->cmd->cmd)
	{
		ft_exec(e);
		if (e->state[0] != 0)
			ft_wait(e);
		e->state[1] = WEXITSTATUS(e->cmd->status);
	}
	if (e->state[1] != 0 || e->state[1] != 0)
		e->status = -1;
	e->file.input = e->cmd->fd_aux[READ];
	e->file.output = e->cmd->fd_aux[WRITE];
	e->cmd--;
	e->status = e->state[1];
	return (e->state);
}
