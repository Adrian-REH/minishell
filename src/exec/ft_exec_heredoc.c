/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:12:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/24 18:27:01 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static int	*ft_exec_give_cmd(t_exec *e)
{
	e->cmd->pid = fork();
	if (e->cmd->pid < 0)
	{
		ft_print_error("fork", 1, "");
		return (NULL);
	}
	else if (e->cmd->pid == 0)
	{
		if (e->file.output == -1)
			(ft_print_error(strerror(errno), 1, NULL));
		if (e->file.input == -1)
			(ft_print_error(strerror(errno), 1, NULL));
		if (dup2(e->file.input, STDIN_FILENO) == -1)
			(close(e->file.input), ft_print_error("dup2: ", 1, "input error"));
		if (e->file.input != 0)
			close(e->file.input);
		if (e->file.output != 1)
		{
			if (dup2(e->file.output, STDOUT_FILENO) == -1)
				(ft_print_error("dup2", 1, NULL));
			close(e->file.output);
		}
		exit(dispatch_command(e));
	}
	return (NULL);
}

int	ft_execute_heredocs(t_exec *e, int *index)
{
	char	*p_heredoc;

	while (1)
	{
		ft_putstr_fd("heredoc>", STDOUT_FILENO);
		p_heredoc = get_next_line(0);
		if (p_heredoc == NULL && get_error(0, 0) >= 0)
		{
			(index[0])++;
			printf("\n");
			return (1);
		}
		if (ft_strcmp(e[*index].file.end_heredoc, p_heredoc) == 0)
		{
			(index[0])++;
			(free(p_heredoc));
			break ;
		}
		(ft_putstr_fd(p_heredoc, e->cmd->fd_aux[WRITE]), free(p_heredoc));
	}
	return (0);
}

static void	get_execute_fds(t_exec *e, int i)
{
	t_exec	*exec;
	int		j;
	int		state;

	exec = ((j = i), e);
	e = &exec[i];
	while (j >= 0 && (exec[j].op == 6))
		j--;
	j++;
	while (j <= i && (exec[j].op == 6))
	{
		state = ft_execute_heredocs(e, &j);
		if (get_error(0, 0) > 0)
			break ;
		if (state)
			continue;
	}
	close(e->cmd->fd_aux[WRITE]);
	e->file.input = ((e->cmd->pid = 0), e->cmd->fd_aux[READ]);
}

int	*ft_exec_heredoc(t_exec *e, int index)
{
	e = &e[index];
	if (e->state[0] == 0)
	{
		//if (e[-1].file.input != 0 && e[-1].op == 6)
		//	ft_concat_fds(e[-1].file.input, e->cmd->fd_aux[WRITE]);
		get_execute_fds((e - index), index);
	}
	if (e->state[1] == 0 && get_error(0, 0) == 0)
		ft_exec_give_cmd(e);
	if (get_error(0, 0) >= 0)
		e->state[1] = 1;
	e->status = e->state[1];
	e->state[0] = e->state[1];
	return (e->state);
}
