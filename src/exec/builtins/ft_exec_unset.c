/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:14:21 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 06:21:27 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	**ft_sarrdel(char **arr, int idx)
{
	char	**new;
	int		i;
	int		j;

	i = -1;
	j = 0;
	new = ft_calloc(sizeof(void *), ft_sarrsize(arr) + 1);
	while (arr[++i])
	{
		if (i == idx)
			continue ;
		new[j++] = arr[i];
	}
	new[j] = NULL;
	return (new);
}

int	ft_exec_unset(struct s_cmd *cmd)
{
	int		i;
	int		j;
	char	**str;
	char	*line;
	size_t	len;

	cmd->status = 0;
	line = ft_strnstr(cmd->line, "unset", ft_strlen(cmd->line));
	if (line)
	{
		len = ft_strlen("unset");
		memmove(line, line + len, strlen(line + len) + 1);
	}
	str = ((line = ft_strtrim(line, " ")), ft_split(line, ' '));
	i = -1;
	while (cmd->handler->env[++i])
	{
		j = -1;
		while (str[++j])
		{
			if (!ft_strncmp(cmd->handler->env[i], str[j], ft_strlen(str[j])))
				cmd->handler->env = ft_sarrdel(cmd->handler->env, i);
		}
	}
	return ((cmd->status = 0), 0);
}
