/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:12:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 08:24:10 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	**do_exec(char *line, char **env)
{
	char	*cmd;
	char	**command;

	if (!line)
		return (NULL);
	command = ft_split(line, ' ');
	if (!command)
		return (perror("Memory error: "), NULL);
	if (*command == 0)
		return (ft_free_p2(command), NULL);
	if ((access(command[0], 0 | 1) == 0) && ft_strnstr(command[0], "./", 2))
		return (command);
	else if (access(command[0], 0 | 1) != 0 && ft_strchr(command[0], '/'))
		return (command);
	else
	{
		cmd = get_path(command[0], env);
		if (cmd != NULL && strcmp(cmd, command[0]) != 0)
			command[0] = (free(command[0]), cmd);
		return (command);
	}
	return (command);
}
