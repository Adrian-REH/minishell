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
        e->file.input = open(e->file.dir_file, O_RDONLY);
        if (e->file.input == -1)
            (ft_print_error(strerror(errno), 1, NULL));
        if (dup2(e->file.input, STDIN_FILENO) == -1)
            (close(e->file.input), ft_print_error(strerror(errno), errno, NULL));
        close(e->file.input);
        if (e->file.output != 1)
        {
            if (dup2(e->file.output, STDOUT_FILENO) == -1)
                (ft_print_error(strerror(errno), errno, NULL));
            close(e->file.output);
        }
        dispatch_command(e);
        exit(0);
    }
    if (e->file.output != 1)
        close(e->file.output);
    if (e->file.input != 0)
        close(e->file.input);
    return NULL;
}
int *ft_exec_less(t_exec *e)
{
    if (e->state[0] == 0)
    {
        ft_exec(e);
        waitpid(e->cmd->pid, &e->cmd->status, 0); // En el caso de que el primer comando falle, el segundo no se ejecuta
        e->state[0] = WEXITSTATUS(e->cmd->status);
    }
    e->status = e->state[0];
    e->state[1] = e->state[0];
    return e->state;
}