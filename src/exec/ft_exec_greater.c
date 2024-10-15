/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_greater.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:12:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/22 23:11:56 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	ft_dup2_infile(char *infile, int input)
{
	if (infile)
	{
		input = open(infile, O_RDONLY, 0644);
		if (input == -1)
			(ft_print_error(strerror(errno), 1, NULL));
		if (dup2(input, STDIN_FILENO) == -1)
			ft_exeption_fd(input, 0, NULL);
	}
	else
	{
		if (dup2(input, STDIN_FILENO) == -1)
			(ft_exeption_fd(input, 0, NULL));
	}
	if (input != 0)
		close(input);
}

static int	*ft_exec(t_exec *e, int index)
{
	t_exec	*exec;

	exec = e;
	e = &exec[index];
	e->cmd->pid = fork();
	if (e->cmd->pid < 0)
		return (ft_print_error("fork", 1, ""), NULL);
	else if (e->cmd->pid == 0)
	{
		get_execute_files(exec, index);
		e->file.output = open(e->file.odfile, 1 | O_WRONLY | O_CREAT, 0644);
		if (e->file.output == -1)
			(ft_print_error(strerror(errno), 1, NULL));
		if (dup2(e->file.output, STDOUT_FILENO) == -1)
			ft_exeption_fd(e->file.input, e->file.output, NULL);
		(close(e->file.output), ft_dup2_infile(e->file.idfile, e->file.input));
		exit(dispatch_command(e));
	}
	return (NULL);
}

int	*ft_exec_greater(t_exec *e, int index)
{
	t_exec	*exec;

	exec = e;
	e = &e[index];
	if (e->state[0] == 0)
	{
		heredoc_read(exec, index, count_redirects(exec, index));
		ft_exec(exec, index);
	}
	e->status = e->state[0];
	e->state[1] = e->state[0];
	return (e->state);
}
