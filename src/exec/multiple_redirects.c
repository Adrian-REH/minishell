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


static void	infile_open(t_exec *e, int i, int *j)
{
	e[i].file.input = open(e[*j].file.idfile, O_RDONLY, 0644);
	if (e[i].file.input == -1)
		(ft_print_error(strerror(errno), 1, NULL));
	e[i].file.idfile = (close(e[i].file.input), e[*j].file.idfile);
	(*j)++;
}

static void	outfile_open(t_exec *e, int i, int *j)
{
	e[i].file.output = open(e[*j].file.odfile, 1 | O_CREAT | O_APPEND, 0644);
	if (e[i].file.output == -1)
		(ft_print_error(strerror(errno), 1, NULL));
	close(e[i].file.output);
	if (!e[i].file.odfile)
		e[i].file.odfile = e[*j].file.odfile;
	(*j)++;
}

void	get_execute_files(t_exec *e, int i)
{
	int		j;
	int		output;
	int		state;

	output = ((j = i), e[i].cmd->fd_aux[WRITE]);
	while (j >= 0 && (e[j].op <= 8 && e[j].op >= 5))
		j--;
	j++;
	while (j < (i + 1) && (e[j].op <= 8 && e[j].op >= 5))
	{
		if (e[j].op == LESS)
			infile_open(e, i, &j);
		else if (e[j].op != 6)
			outfile_open(e, i, &j);
		else if (e[j].op == 6)
		{
			state = ft_execute_heredocs(e[j].file.end_heredoc, &j, output);
			if (get_error() > 0)
				break ;
			if (state)
				continue ;
		}
	}
	close(output);
	e[i].file.input = ((e[i].cmd->pid = 0), e[i].cmd->fd_aux[READ]);
}
