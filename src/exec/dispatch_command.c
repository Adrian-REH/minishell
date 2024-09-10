#include "../headers/minishell.h"

int dispatch_command(t_exec *e)
{
	int type;

	type = ft_isbuiltin(e->handler->builtins, e->cmd->line);
	if ((type < 4 && type >= 0) || type == NOT_OPERATOR)
	{
		if (execve(e->cmd->cmd[0], e->cmd->cmd, e->handler->env) == -1)
			ft_print_error("command not found: ", 127, e->cmd->cmd[0]);
	}
	else if ((type >= 4 && type <= 7) && e->handler->fb[type])
	{
		e->handler->fb[type](e->cmd);
	}
	e->state[0] = e->cmd->status;
	return e->cmd->status;
}

int dispatch_command_built(t_exec *e)
{
	int type;

	e->state = 0;
	type = ft_isbuiltin(e->handler->builtins, e->cmd->line);
	if (type == NOT_OPERATOR)
	{
		// Verificar si es un directorio o no
		if (execve(e->cmd->cmd[0], e->cmd->cmd, e->handler->env) == -1)
			ft_print_error("command not found: ", 127, e->cmd->cmd[0]);
	}
	else
		e->handler->fb[type](e->cmd);
	return 0;
}