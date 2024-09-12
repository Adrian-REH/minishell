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
        e->file.output = open(e->file.dir_file, O_WRONLY | O_CREAT, 0777);
        if (e->file.output == -1)
            (ft_putstr_fd(" No such file or directory", 2), exit(1));
        if (dup2(e->file.output, STDOUT_FILENO) == -1)
            (close(e->file.output), ft_print_error("dup2", 1, NULL));
        if (dup2(e->file.input, STDIN_FILENO) == -1)
            (close(e->file.input), ft_print_error("dup2", 1, NULL));
        close(e->file.output);
        dispatch_command(e);
        exit(0);
    }
    return NULL;
}
int *ft_exec_greater(t_exec *e)
{
    if (e->state[0] == 0)
    {
        ft_exec(e);
        waitpid(e->cmd->pid, &e->cmd->status, 0); // En el caso de que el primer comando falle, el segundo no se ejecuta
        e->state[0] = WEXITSTATUS(e->cmd->status);
    }
    if (e->state[0] != 0)
        e->status = 1;
    return e->state;
}