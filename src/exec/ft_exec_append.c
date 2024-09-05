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
        if (dup2(e->file.input, STDIN_FILENO) == -1)
            (close(e->file.input), ft_print_error("dup2", 1, NULL));
        close(e->file.input);
        if (execve(e->cmd->cmd[0], e->cmd->cmd, e->handler->env) == -1) // Se supone que ya se verifico que el path esta bien y que se puede ejecutar directamente.
            ft_print_error("command not found: ", 127, e->cmd->cmd[0]);
        exit(0);
    }
    return NULL;
}
int *ft_exec_append(t_exec *e)
{
    if (e->state[0] == 0)
    {
        ft_exec(e);
        waitpid(e->cmd->pid, &e->cmd->status, 0); // En el caso de que el primer comando falle, el segundo no se ejecuta
        e->state[0] = WEXITSTATUS(e->cmd[0].pid);
    }
    if (e->state[1] != 0 || e->state[1] != 0)
        e->status = -1;
    e->handler->code = e->state[1];
    return e->state;
}