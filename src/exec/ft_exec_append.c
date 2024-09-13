#include "../headers/minishell.h"

static int *ft_exec(t_exec *e, int index)
{
    int j;
    t_exec *exec;

    exec = e;
    e = &exec[index];
    j = index;
    while (exec[j].op == GREATER || exec[j].op == APPEND)
        j--;
    e->cmd->pid = fork();
    if (e->cmd->pid < 0)
    {
        ft_print_error("fork", 1, "");
        return NULL;
    }
    else if (e->cmd->pid == 0)
    {
        while (exec[++j].op == GREATER || exec[j].op == APPEND)
        {
            e->file.output = open(exec[j].file.dir_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (e->file.output == -1)
                (ft_print_error(strerror(errno), 1, NULL));
            close(e->file.output);
        }
        e->file.output = open(e->file.dir_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (e->file.output == -1)
            (ft_print_error(strerror(errno), 1, NULL));
        if (dup2(e->file.output, STDOUT_FILENO) == -1)
            (close(e->file.output), ft_print_error("dup2", 1, NULL));
        close(e->file.output);
        if (dup2(e->file.input, STDIN_FILENO) == -1)
            (close(e->file.input), ft_print_error("dup2", 1, NULL));
        dispatch_command(e);
        exit(0);
    }
    return NULL;
}
int *ft_exec_append(t_exec *e, int index)
{
    t_exec *exec;
    exec = e;
    e = &e[index];
    if (e->state[0] == 0)
    {
        ft_exec(exec, index);
        waitpid(e->cmd->pid, &e->cmd->status, 0); // En el caso de que el primer comando falle, el segundo no se ejecuta
        e->state[0] = WEXITSTATUS(e->cmd->status);
    }
    e->status = e->state[0];
    e->state[1] = e->state[0];
    return e->state;
}