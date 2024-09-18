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

static void	ft_handler_env(t_cmd *cmd, char **str, char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if ((ft_isalpha(line[i]) && line[i + 1] == '-' ) && \
		(!line[i + 2] || line[i + 2] == '='))
		{
			ft_putstr_fd(" not a valid identifier\n", 2);
			cmd->status = 1;
		}
	}
	str = ((i = -1), ft_split(line, '='));
	if (!str || !str[0])
		cmd->status = (ft_putstr_fd(" not a valid identifier\n", 2), 1);
	else if (ft_isdigit(str[0][0]))
		cmd->status = (ft_putstr_fd(" not a valid identifier\n", 2), 1);
	if (cmd->status)
		return (ft_free_p2(str));
	while (cmd->handler->env[++i])
		if (ft_strncmp(cmd->handler->env[i], str[0], ft_strlen(str[0])) == 0)
			cmd->handler->env[i] = (free(cmd->handler->env[i]), line);
	if (i == ft_sarrsize(cmd->handler->env))
		cmd->handler->env = ft_sarradd(cmd->handler->env, line);
	ft_free_p2(str);
}

int	ft_exec_export(struct s_cmd *cmd)
{
	char	*line;
	size_t	len;

	cmd->status = 0;
	line = ft_strnstr(cmd->line, "export", ft_strlen(cmd->line));
	if (line)
	{
		len = ft_strlen("export");
		ft_memmove(line, line + len, strlen(line + len) + 1);
	}
	line = ft_strtrim(line, " ");
	ft_handler_env(cmd, NULL, line);
	return (cmd->status);
}
