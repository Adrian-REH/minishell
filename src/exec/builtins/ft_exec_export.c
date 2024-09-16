/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:14:11 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 06:21:19 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_exec_export(struct s_cmd *cmd)
{
	int		i;
	char	**str;
	char	*line;
	size_t	len;

	line = ft_strnstr(cmd->line, "export", ft_strlen(cmd->line));
	if (line)
	{
		len = ft_strlen("export");
		ft_memmove(line, line + len, strlen(line + len) + 1);
	}
	line = ft_strtrim(line, " ");
	i = -1;
	while (line[++i])
	{
		if ((ft_isalpha(line[i]) && line[i + 1] == '-' ) && (!line[i + 2] || line[i + 2] == '='))
		{
			ft_putstr_fd(" not a valid identifier\n", 2);
			cmd->status = 1;
			return ;
		}
	}
	str = ft_split(line, '=');
	if (!str || !str[0])
	{
		ft_putstr_fd(" not a valid identifier\n", 2);
		cmd->status = 1;
		return ;
	}
	if (ft_isdigit(str[0][0]))
	{
		ft_putstr_fd(" not a valid identifier\n", 2);
		cmd->status = 1;
		return ;
	}
	i = -1;
	while (cmd->handler->env[++i])
	{
		if (ft_strncmp(cmd->handler->env[i], str[0], ft_strlen(str[0])) == 0)
		{
			free(cmd->handler->env[i]);
			cmd->handler->env[i] = line;
		}
	}
	if (i == ft_sarrsize(cmd->handler->env))
		cmd->handler->env = ft_sarradd(cmd->handler->env, line);
	cmd->status = 0;
	return ;
}
