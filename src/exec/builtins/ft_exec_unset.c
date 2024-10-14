/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:14:21 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/20 23:21:06 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	del_env(struct s_cmd *cmd, char **str)
{
	int	i;
	int	j;

	i = -1;
	while (cmd->handler->env[++i])
	{
		j = -1;
		while (str[++j])
		{
			if (!ft_strncmp(cmd->handler->env[i], str[j], ft_strlen(str[j])))
				cmd->handler->env = ft_sarrdelbyindex(cmd->handler->env, i);
		}
	}
}

int	ft_exec_unset(struct s_cmd *cmd)
{
	char	**str;
	char	*line;
	size_t	len;

	cmd->status = 0;
	line = ft_strnstr(cmd->line, "unset", ft_strlen(cmd->line));
	if (line && (line[5] == ' ' || line[5] == 0))
	{
		len = ft_strlen("unset");
		ft_memmove(line, line + len, strlen(line + len) + 1);
	}
	else
	{
		cmd->status = (ft_putstr_fd("command not found\n", 2), 127);
		return (127);
	}
	str = ((line = ft_strtrim(line, " ")), ft_split(line, ' '));
	del_env(cmd, str);
	return ((cmd->status = 0), 0);
}
