/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:12:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 06:21:30 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_exec_file(t_exec *e)
{
	int		fd;
	int		fd2;
	char	*line;

	if (ft_strchr(e->cmd->cmd[0], '/') && (access(e->cmd->cmd[0], X_OK) == -1))
		ft_print_error(" Permission denied", 126, NULL);
	fd = open(e->cmd->cmd[0], O_RDONLY);
	if (fd == -1)
		ft_print_error(strerror(errno), errno, NULL);
	fd2 = open("temp", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	line = get_next_line(fd);
	write(fd2, "#!/bin/bash\n", ft_strlen("#!/bin/bash"));
	while (line)
	{
		write(fd2, line, ft_strlen(line));
		line = get_next_line(fd);
	}
	close(fd2);
	close(fd);
	if (execve("temp", (char *[]){"temp", NULL}, e->handler->env) == -1)
		(unlink("temp"), ft_print_error(" command not found", 2, NULL));
}

static void	execute_command(t_exec *e)
{
	struct stat	path_stat;

	if (ft_strchr(e->cmd->cmd[0], '$') && (ft_isalpha(e->cmd->cmd[0][1])))
	{
		e->cmd->cmd[0] = ft_getenv(e->cmd, ft_strchr(e->cmd->cmd[0], '$') + 1);
		if (!e->cmd->cmd[0])
			exit(0);
	}
	if (stat(e->cmd->cmd[0], &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode) && ft_strchr(e->cmd->cmd[0], '/'))
			ft_print_error(" Is a directory", 126, NULL);
		if (S_ISREG(path_stat.st_mode))
		{
			if (execve(e->cmd->cmd[0], e->cmd->cmd, e->handler->env) == -1)
				ft_exec_file(e);
		}
	}
	if (execve(e->cmd->cmd[0], e->cmd->cmd, e->handler->env) == -1)
		ft_print_error(" command not found", 127, NULL);
}

int	dispatch_command(t_exec *e)
{
	int	type;

	e->cmd->status = 0;
	type = ft_isbuiltin(e->handler->builtins, e->cmd->line);
	if (type == NOT_OPERATOR)
		execute_command(e);
	else if (e->handler->fb[type])
		e->cmd->status = e->handler->fb[type](e->cmd);
	return (e->cmd->status);
}

int	dispatch_command_built(t_exec *e)
{
	int			type;

	e->state = 0;
	type = ft_isbuiltin(e->handler->builtins, e->cmd->line);
	if (type == NOT_OPERATOR)
		execute_command(e);
	else
		e->cmd->status = e->handler->fb[type](e->cmd);
	return (e->cmd->status);
}
