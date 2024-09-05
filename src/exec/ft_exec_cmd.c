#include "../headers/minishell.h"

static int *ft_exec(t_exec *e)
{
	e->cmd->pid = fork();
	if (e->cmd->pid < 0)
	{
		ft_print_error("fork", 1, "");
		return NULL;
	}
	else if (e->cmd->pid == 0)
	{
		dispatch_command(e);
		exit(0);
	}
	return NULL;
}
int *ft_exec_cmd(t_exec *e)
{
	int type;
	type = ft_isbuiltin(e->handler->builtins, e->cmd->line);

	if (e->state[0] == 0 && ((type < 4  && type >= 0) || type == NOT_OPERATOR))
	{
		ft_exec(e);
		waitpid(e->cmd->pid, &e->cmd->status, 0); // En el caso de que el primer comando falle, el segundo no se ejecuta
		e->state[0] = WEXITSTATUS(e->cmd[0].pid);
	}else if (type >= 4 && type <= 7)
	{
		e->handler->fb[type](e->cmd);
	}

	if (e->state[1] != 0 || e->state[1] != 0)
		e->status = -1;
    e->handler->code = e->state[0];
	return e->state;
}