#include "../headers/minishell.h"

int dispatch_command(t_exec *e)
{
	int type;

	e->cmd->status = 0;
	type = ft_isbuiltin(e->handler->builtins, e->cmd->line);

	if (type == NOT_OPERATOR)
	{
		ft_putstr_fd("minishell: \n", STDERR_FILENO);
		if (execve(e->cmd->cmd[0], e->cmd->cmd, e->handler->env) == -1)
				(ft_print_error(strerror(errno), errno, NULL));
	}
	else if (e->handler->fb[type])
	{
		e->handler->fb[type](e->cmd);
	}
	return e->cmd->status;
}

int dispatch_command_built(t_exec *e)
{
	int type;

	e->state = 0;
	type = ft_isbuiltin(e->handler->builtins, e->cmd->line);
	if (type == NOT_OPERATOR)
	{
		if (execve(e->cmd->cmd[0], e->cmd->cmd, e->handler->env) == -1)
			ft_print_error("command not found: ", 127, e->cmd->cmd[0]);
	}
	else
		e->handler->fb[type](e->cmd);
	return e->cmd->status;
}