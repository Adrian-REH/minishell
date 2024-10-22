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
	(exec[i].op == 3 || exec[i].op == 6 || exec[i].op == 5))
	{
		close(b->fd[1]);
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
	if (++j == 1 && 1 != b->len_exec && \
	(exec[i].op == PIPE || exec[i + 1].op == PIPE || exec[i].op == 5))
	{
		exec[i].file.output = (b->fd[1]);
		if (exec[i].op == 5)
			exec[i].file.input = (b->fd[0]);
	}
	else if (j == b->len_exec && \
	(exec[i].op == PIPE || exec[i].op == HEREDOC || exec[i].op == LESS))
		exec[i].file.output = 1;
}
