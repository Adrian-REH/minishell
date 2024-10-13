/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:12:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/21 17:53:18 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static int	*ft_exec(t_exec *e)
{
	e->cmd->pid = fork();
	if (e->cmd->pid < 0)
	{
		ft_print_error("fork", 1, "");
		return (NULL);
	}
	else if (e->cmd->pid == 0)
	{
		if (dup2(e->file.input, STDIN_FILENO) == -1)
			ft_exeption_fd(e->file.input, 0, e->cmd->fd_aux);
		if (e->file.input != 0)
			close(e->file.input);
		if (e->file.output != 1)
			close(e->file.output);
		if (dup2(e->cmd->fd_aux[WRITE], STDOUT_FILENO) == -1)
			(ft_exeption_fd(0, 0, e->cmd->fd_aux));
		(close(e->cmd->fd_aux[WRITE]), close(e->cmd->fd_aux[READ]));
		exit(dispatch_command(e));
	}
	if (e->file.input != 0)
		close(e->file.input);
	close(e->cmd->fd_aux[WRITE]);
	e->file.input = e->cmd->fd_aux[READ];
	return (NULL);
}

static int	*ft_exec_sec_cmd(t_exec *e)
{
	e->cmd->pid = fork();
	if (e->cmd->pid < 0)
	{
		ft_print_error("fork", 1, "");
		return (NULL);
	}
	else if (e->cmd->pid == 0)
	{
		if (dup2(e->file.input, STDIN_FILENO) == -1)
			(ft_print_error("dup2: ", 1, "input error"));
		if (e->file.input != 0)
			close(e->file.input);
		if (dup2(e->file.output, STDOUT_FILENO) == -1)
			(ft_print_error("dup2", 1, NULL));
		if (e->file.output != 1)
			close(e->file.output);
		exit(dispatch_command(e));
	}
	if (e->file.input != 0)
		close(e->file.input);
	if (e->file.output != 1)
		close(e->file.output);
	return (NULL);
}

int	*ft_exec_pipe(t_exec *exec, int index)
{
	char	*p_heredoc;
	t_exec	*e;

	e = &exec[index];
	if (e->state[1] == 1)
	{
		ft_putstr_fd(">", STDOUT_FILENO);
		p_heredoc = get_next_line(STDIN_FILENO);
		p_heredoc = ft_strtrim(p_heredoc, "\n");
		e->cmd[1].cmd = do_exec(p_heredoc, e->handler->env);
	}
	if (e->state[0] == 0)
		ft_exec(e);
	e->cmd++;
	if (e->state[1] == 0)
		ft_exec_sec_cmd(e);
	e->cmd--;
	e->status = e->state[1];
	return (e->state);
}
