#include "../headers/minishell.h"

int dispatch_command(t_exec *e)
{
	int type;

	type = ft_isbuiltin(e->handler->builtins, e->cmd->line);
	if (type == NOT_OPERATOR)
	{
		if (execve(e->cmd->cmd[0], e->cmd->cmd, e->handler->env) == -1)
			ft_print_error("command not found: ", 127, e->cmd->cmd[0]);
	}
	else
		e->handler->fb[type](e->cmd);
	return 0;
}
