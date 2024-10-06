/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:14:16 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 06:21:22 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_exec_pwd(t_cmd *cmd)
{
	int		i;
	char	*line;

	i = -1;
	line = ft_strnstr(cmd->line, "pwd", ft_strlen(cmd->line));
	if (!line || (line[3] != 0 || line[3] != ' '))
	{
		cmd->status = (ft_putstr_fd("command not found\n", 2), 127);
		return (127);
	}
	while (cmd->handler->env[++i])
	{
		if (!ft_strncmp(cmd->handler->env[i], "PWD", 3))
			printf("%s\n", cmd->handler->env[i] + 4);
	}
	return (0);
}
