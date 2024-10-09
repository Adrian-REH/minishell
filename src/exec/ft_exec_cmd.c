/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:12:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 08:17:10 by adherrer         ###   ########.fr       */
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
		exit(dispatch_command_built(e));
	}
	return (NULL);
}

int	*ft_exec_cmd(t_exec *e, int index)
{
	int	type;

	e = &e[index];
	type = ft_isbuiltin(e->handler->builtins, e->cmd->line);
	if (e->state[0] == 0 && ((type < 4 && type >= 0) || type == NOT_OPERATOR))
		ft_exec(e);
	else if ((type >= 4) && e->handler->fb[type])
	{
		e->handler->fb[type](e->cmd);
		e->state[0] = e->cmd->status;
	}
	e->status = e->state[0];
	e->state[1] = e->state[0];
	return (e->state);
}
