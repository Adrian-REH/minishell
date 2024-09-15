/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:14:08 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 06:21:17 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void ft_exec_exit(struct s_cmd *cmd)
{
	char **str;
	char *line;
	size_t len;
	cmd->status = 0;
	line = ft_strnstr(cmd->line, "exit", ft_strlen(cmd->line));
	if (line)
	{
		len = ft_strlen("exit"); // Longitud de la subcadena
		memmove(line, line + len, strlen(line + len) + 1);
	}
	line = ft_strtrim(line, " ");

	str = ft_split(line, ' ');
	if (ft_sarrsize(str) > 1)
	{
		ft_putstr_fd(" too many arguments\n", 2);
		cmd->status = 1;
		return;
	}
	if (ft_isdigit(*line) == 0 && *line != '\"' && *line != '-' && *line != '+')
	{
		ft_putstr_fd(" numeric argument required\n", 2);
		cmd->status = 2;
		return;
	}
	int i = -1;
	int sig = 0;
	while (line[++i])
	{
		if (line[i] == '-' || line[i] == '+')
		{
			sig = -1;
			if (line[i] == '+')
				sig = 1;
			continue;
		}
		if (line[i] == ' ')
			break;
		if (line[i] == '\"')
			continue;
		if (sig == -1)
			cmd->status = cmd->status * 10 - (line[i] - '0');
		else
			cmd->status = cmd->status * 10 + (line[i] - '0');
	}
	cmd->status = cmd->status % 256;
	exit(cmd->status);
	printf("%s\n", cmd->line);
}