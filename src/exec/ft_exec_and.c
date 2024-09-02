#include "../headers/minishell.h"

static int *ft_exec(t_exec *e)
{
	// if (pipe(e->file.fd_aux) == -1)
	//	return (ft_print_error("pipe", 1, ""), NULL);
	e->cmd->pid = fork();
	if (e->cmd->pid < 0)
	{
		ft_print_error("fork", 1, "");
		return NULL;
	}
	else if (e->cmd->pid == 0)
	{
		/* 		if (dup2(e->file.fd_aux[WRITE], STDOUT_FILENO) == -1)
					(close(e->file.fd_aux[WRITE]), close(e->file.fd_aux[READ]), ft_print_error("dup2", 1, NULL));
				if (dup2(e->file.fd_aux[READ], STDIN_FILENO) == -1)
					(close(e->file.fd_aux[WRITE]), close(e->file.fd_aux[READ]), ft_print_error("dup2", 1, NULL));
				(close(e->file.fd_aux[WRITE]), close(e->file.fd_aux[READ]));
		 */
		if (execve(e->cmd->cmd[0], e->cmd->cmd, e->handler->env) == -1) // Se supone que ya se verifico que el path esta bien y que se puede ejecutar directamente.
			ft_print_error("command not found: ", 127, e->cmd->cmd[0]);
	}
	//(close(e->file.fd_aux[WRITE]), close(e->file.fd_aux[READ]));
	return NULL;
}

int *ft_exec_and(t_exec *e)
{
	printf("sadasdsad\n");
	if (e->state[0] == 0 && e->cmd[0].cmd)
	{
		ft_exec(e);
		waitpid(e->cmd->pid, &e->cmd->status, 0); // En el caso de que el primer comando falle, el segundo no se ejecuta
		e->state[0] = WEXITSTATUS(e->cmd->status);
	}
	printf("sadasdsad\n");
	if (e->state[0] == 0 && e->cmd[1].cmd)
	{
		ft_exec(e);
		waitpid(e->cmd[1].pid, &e->cmd[1].status, 0);
		e->state[1] = WEXITSTATUS(e->cmd[1].status);
	}
	if (e->state[1] != 0 || e->state[1] != 0)
		e->status = -1;
	return e->state;
}