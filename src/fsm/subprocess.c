/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:12:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 08:16:54 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_handler	*ft_subprocess(t_handler *handler)
{
	int		i;
	pid_t	result;
	int		status;

	if (get_error() != 130 && get_error() != 131)
		return (handler);
	if (handler->w_cmd)
	{
		i = -1;
		while (i < handler->n_pids && handler->w_cmd[++i].pid)
		{
			result = waitpid(handler->w_cmd[i].pid, &status, WNOHANG);
			if (result == handler->w_cmd[i].pid)
			{
				printf("[%d] Done\t\t\t%s\n", i + 1, handler->w_cmd[i].cmd[0]);
				handler->n_pids--;
				handler->w_cmd = delete_cmd(handler->w_cmd, i);
				i--;
			}
		}
	}
	return (handler);
}
