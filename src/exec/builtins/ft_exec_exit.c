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

static int	handler_exit_result(char *line, t_cmd *cmd)
{
	int	i;
	int	sig;

	if (ft_isdigit(*line) == 0 && *line != '\"' && *line != '-' && *line != '+')
		return (ft_putstr_fd(" numeric argument required\n", 2), 2);
	sig = ((i = -1), 0);
	while (line[++i])
	{
		if (line[i] == '-' || line[i] == '+')
		{
			sig = -1;
			if (line[i] == '+')
				sig = 1;
			continue ;
		}
		if (line[i] == ' ')
			break ;
		if (line[i] == '\"')
			continue ;
		if (sig == -1)
			cmd->status = cmd->status * 10 - (line[i] - '0');
		else
			cmd->status = cmd->status * 10 + (line[i] - '0');
	}
	return (0);
}

/*
LLama a la funcion handler_exit_result para verificar liberar memoria
*/
int	ft_exec_exit(struct s_cmd *cmd)
{
	char	**str;
	char	*line;
	size_t	len;

	cmd->status = 0;
	line = ft_strnstr(cmd->line, "exit ", ft_strlen("exit "));
	if (line)
	{
		len = ft_strlen("exit ");
		ft_memmove(line, line + len, strlen(line + len) + 1);
	}
	else
	{
		cmd->status = (ft_putstr_fd("command not found\n", 2), 127);
		return (127);
	}
	line = ft_strtrim(line, " ");
	if (!line)
		cmd->status = (ft_putstr_fd("Error malloc\n", 2), 1);
	str = ft_split(line, ' ');
	if (!str)
		return ((cmd->status = 1), ft_putstr_fd("Error malloc\n", 2), 0);
	if (str[0] == 0)
		exit(cmd->status);
	if (ft_sarrsize(str) > 1)
		return ((cmd->status = 1), ft_putstr_fd(" too many arguments\n", 2), 0);
	len = handler_exit_result(line, cmd);
	if (len != 0)
		return ((cmd->status = len), len);
	return (exit(cmd->status % 256), 0);
}
