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
		printf("input_c: %d | output_c: %d\n", e->file.input, e->file.output);
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
	if (e->file.output != 1)
		close(e->file.output);
	return (NULL);
}

int	ft_execute_heredocs(char *end_heredoc, int *index, int output)
{
	char	*p_heredoc;

	while (1)
	{
		ft_putstr_fd("heredoc>", STDOUT_FILENO);
		p_heredoc = get_next_line(0);
		if (p_heredoc == NULL && get_error() >= 0)
		{
			(index[0])++;
			printf("\n");
			return (1);
		}
		if (ft_strcmp(end_heredoc, p_heredoc) == 0)
		{
			(index[0])++;
			(free(p_heredoc));
			break ;
		}
		(ft_putstr_fd(p_heredoc, output), free(p_heredoc));
	}
	return (0);
}

static void	get_execute_fds(t_exec *e, int i)
{
	int		j;
	int		state;
	int		output;

	j = i;
	output = e[i].cmd->fd_aux[WRITE];
	while (j >= 0 && (e[j].op == 6))
		j--;
	j++;
	while (j < (i + 1) && (e[j].op == 6))
	{
		state = ft_execute_heredocs(e[j].file.end_heredoc, &j, output);
		if (get_error() > 0)
			break ;
		if (state)
			continue ;
	}
	close(output);
	e[i].file.input = ((e[i].cmd->pid = 0), e[i].cmd->fd_aux[READ]);
}

int	*ft_exec_heredoc(t_exec *e, int index)
{
	if (e[index].state[0] == 0)
		get_execute_fds(e, index);
	e = &e[index];
	if (e->state[1] == 0 && get_error() == 0)
		ft_exec_give_cmd(e);
	if (get_error() >= 0)
		e->state[1] = 1;
	e->status = e->state[1];
	e->state[0] = e->state[1];
	return (e->state);
}
