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

int	reemplace_env(t_cmd *cmd, char **str, char *line)
{
	int	i;

	i = -1;
	while (cmd->handler->env[++i])
		if (ft_strncmp(cmd->handler->env[i], str[0], ft_strlen(str[0])) == 0)
		{
			if (ft_strchr(cmd->handler->env[i] + ft_strlen(str[0]), '=') == 0)
			{
				cmd->handler->env[i] = (free(cmd->handler->env[i]), line);
				return (1);
			}
		}
	return (0);
}

static void	ft_save_env(t_cmd *cmd, char **str, char *line)
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
	str = (ft_split(line, '='));
	if (!str || !str[0])
		cmd->status = (ft_putstr_fd(" not a valid identifier\n", 2), 1);
	else if (ft_isdigit(str[0][0]))
		cmd->status = (ft_putstr_fd(" not a valid identifier\n", 2), 1);
	if (cmd->status)
		return (ft_free_p2(str));
	if (!reemplace_env(cmd, str, line))
		cmd->handler->env = ft_sarradd(cmd->handler->env, line);
	ft_free_p2(str);
}

char	*expand_env(char *result, struct s_cmd *cmd)
{
	char	*tmp;
	char	**arr;
	int		j;

	j = 0;
	arr = NULL;
	arr = ft_split(result, '$');
	if (!arr)
		return (NULL);
	while (arr[++j])
	{
		tmp = extract_env(arr[j], arr[j], cmd, 0);
		if (tmp)
			arr[j] = (tmp);
		else
			arr[j] = (ft_strdup(""));
	}
	return (ft_sarrtostr(arr, ""));
}

int	ft_exec_export(struct s_cmd *cmd)
{
	char	*line;
	char	*tmp;
	size_t	len;

	cmd->status = 0;
	line = ft_strnstr(cmd->line, "export", ft_strlen(cmd->line));
	if (line && (line[6] == ' ' || line[6] == 0))
	{
		len = ft_strlen("export");
		ft_memmove(line, line + len, strlen(line + len) + 1);
	}
	else
	{
		cmd->status = (ft_putstr_fd("command not found\n", 2), 127);
		return (127);
	}
	line = ft_strtrim(line, " ");
	tmp = expand_env(line, cmd);
	if (!tmp)
		ft_save_env(cmd, NULL, line);
	else
	{
		(ft_save_env(cmd, NULL, tmp));
	}
	return (cmd->status);
}
