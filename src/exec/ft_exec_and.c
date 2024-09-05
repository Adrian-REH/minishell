#include "../headers/minishell.h"

static int *ft_exec(t_exec *e)
{
	e->cmd->pid = fork();
	if (e->cmd->pid < 0)
		return (ft_print_error("fork", 1, ""), NULL);
	else if (e->cmd->pid == 0)
	{
		dispatch_command(e);
		exit(0);
	}
	return NULL;
}

int *ft_exec_and(t_exec *e)
{
	char *p_heredoc;
	if (e->state[1] != 0)
	{
		ft_putstr_fd(">", STDOUT_FILENO);
		p_heredoc = get_next_line(STDIN_FILENO);
		p_heredoc = ft_strtrim(p_heredoc, "\n");
		e->cmd[1].cmd = do_exec(p_heredoc, e->handler->env);
	}
	if (e->state[0] == 0)
	{
		ft_exec(e);
		waitpid(e->cmd->pid, &e->cmd->status, 0); // En el caso de que el primer comando falle, el segundo no se ejecuta
		e->state[0] = WEXITSTATUS(e->cmd->status);
	}
	e->cmd++;
	if (e->state[0] == 0)
	{
		ft_exec(e);
		waitpid(e->cmd->pid, &e->cmd->status, 0); // En el caso de que el primer comando falle, el segundo no se ejecuta
		e->state[0] = WEXITSTATUS(e->cmd->status);
	}
	e->cmd--;
	if (e->state[1] != 0 || e->state[1] != 0)
		e->status = -1;
    e->handler->code = e->state[1];
	return e->state;
}