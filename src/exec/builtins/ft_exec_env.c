/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:14:05 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 06:21:14 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_exec_env(struct s_cmd *cmd)
{
	char	*line;

	line = ft_strnstr(cmd->line, "env", ft_strlen(cmd->line));
	if (!line || (line[3] != 0))
	{
		cmd->status = (ft_putstr_fd("command not found\n", 2), 127);
		return (127);
	}
	ft_sarrprint(cmd->handler->env);
	cmd->status = 0;
	return (0);
}
