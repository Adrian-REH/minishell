#include "../headers/minishell.h"
#include <sys/types.h>

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
        if (execve(e->cmd->cmd[0], e->cmd->cmd, e->handler->env) == -1) // Se supone que ya se verifico que el path esta bien y que se puede ejecutar directamente.
            ft_print_error("command not found: ", 127, e->cmd->cmd[0]);
        exit(0);
    }
    return NULL;
}

void *ft_realloc(void *ptr, size_t size)
{
    void *new;

    new = malloc(size);
    if (!new)
        return NULL;
    if (ptr)
    {
        ft_memcpy(new, ptr, size);
        free(ptr);
    }
    return new;
}
pid_t *add_pid(pid_t *pids, pid_t pid)
{
    int i;

    i = 0;
    if (pids == NULL)
    {
        pids = ft_calloc(sizeof(pid_t), 2);
        pids[0] = pid;
        pids[1] = 0;
        return pids;
    }
    while (pids[i])
        i++;
    pids = ft_realloc(pids, sizeof(pid_t) * (i + 2));
    pids[i++] = pid;
    pids[i] = 0;
    return pids;
}

int *ft_exec_amper(t_exec *e)
{
    pid_t result;
    if (e->state[0] == 0)
    {
        ft_exec(e);
        result = waitpid(e->cmd->pid, &e->cmd->status, WNOHANG); // En el caso de que el primer comando falle, el segundo no se ejecuta
        e->state[0] = WEXITSTATUS(e->cmd[0].pid);
        if (result == 0)
        {
            e->handler->n_pids++;
            printf("[%d] %d\n", e->handler->n_pids, e->cmd->pid);
            e->handler->pids = add_pid(e->handler->pids, e->cmd->pid);
        }
    }
    e->cmd++;
    if (e->state[1] == 0 && e->cmd->cmd)
    {
        ft_exec(e);
        if (e->cmd->towait)
            waitpid(e->cmd->pid, &e->cmd->status, 0); // En el caso de que el primer comando falle, el segundo no se ejecuta
        else
        {
            result = waitpid(e->cmd->pid, &e->cmd->status, WNOHANG); // En el caso de que el primer comando falle, el segundo no se ejecuta
            if (result == 0)
            {
                e->handler->n_pids++;
                printf("[%d] %d\n", e->handler->n_pids, e->cmd->pid);
                if (e->handler->pids)
                    e->handler->pids = add_pid(e->handler->pids, e->cmd->pid);
            }
        }
        e->state[1] = WEXITSTATUS(e->cmd[0].pid);
    }

    if (e->state[1] != 0 || e->state[1] != 0)
        e->status = -1;
    e->file.input = e->cmd->fd_aux[READ];
    e->file.output = e->cmd->fd_aux[WRITE];
    return e->state;
}
