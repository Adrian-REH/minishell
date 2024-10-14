/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_less.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:12:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/22 23:11:56 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	ft_dup2_outfile(char *outfile, int output)
{
	if (outfile)
	{
		output = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (output == -1)
			(ft_exeption_fd(0, output, NULL));
	}
	else if (output != 1)
	{
		if (dup2(output, STDOUT_FILENO) == -1)
			(ft_exeption_fd(0, output, NULL));
	}
	if (output != 1)
		close(output);
}

static char	*get_execute_fds(t_exec *e, int i, int j)
{
	t_exec	*exec;
	char	*outfile;
	int		out;

	exec = e;
	outfile = NULL;
	e = &exec[i];
	while (++j < i && (exec[j].op == 7 || exec[j].op == 8 || exec[j].op == 5))
	{
		if (exec[j].op == LESS)
		{
			e->file.input = open(exec[j].file.idfile, O_RDONLY, 0644);
			if (e->file.input == -1)
				(ft_print_error(strerror(errno), 1, NULL));
			close(e->file.input);
		}
		else
		{
			out = open(exec[j].file.odfile, 1 | O_CREAT | O_APPEND, 0644);
			if (out == -1)
				(ft_print_error(strerror(errno), 1, NULL));
			outfile = (close(out), exec[j].file.odfile);
		}
	}
	return (outfile);
}

static int	*ft_exec(t_exec *e, int index)
{
	int		j;
	char	*outfile;
	t_exec	*exec;

	e = ((exec = e), &exec[index]);
	outfile = ((j = index), NULL);
	while (j >= 0 && (exec[j].op == 7 || exec[j].op == 8 || exec[j].op == 5))
		j--;
	e->cmd->pid = fork();
	if (e->cmd->pid < 0)
		return (ft_print_error("fork", 1, ""), NULL);
	else if (e->cmd->pid == 0)
	{
		outfile = get_execute_fds(exec, index, j);
		e->file.input = open(e->file.idfile, O_RDONLY, 0644);
		if (e->file.input == -1)
			(ft_print_error(strerror(errno), 1, NULL));
		if (dup2(e->file.input, STDIN_FILENO) == -1)
			ft_exeption_fd(e->file.input, e->file.output, NULL);
		(close(e->file.input), ft_dup2_outfile(outfile, e->file.output));
		exit(dispatch_command(e));
	}
	return (NULL);
}

int	*ft_exec_less(t_exec *e, int index)
{
	t_exec	*exec;

	exec = e;
	e = &e[index];
	if (e->state[0] == 0)
	{
		ft_exec(exec, index);
		if (e->file.output != 1)
			close(e->file.output);
		if (e->file.input != 0)
			close(e->file.input);
	}
	e->status = e->state[0];
	e->state[1] = e->state[0];
	return (e->state);
}
