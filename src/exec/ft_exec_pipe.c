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
            (close(e->cmd->fd_aux[1]), close(e->cmd->fd_aux[0]), ft_print_error("dup2", 1, ""));
        if (e->file.input != 0)
            close(e->file.input);
        if (e->file.output != 1)
            close(e->file.output);
        if (dup2(e->cmd->fd_aux[WRITE], STDOUT_FILENO) == -1)
            (close(e->cmd->fd_aux[WRITE]), close(e->cmd->fd_aux[READ]), ft_print_error("dup2", 1, NULL));
        (close(e->cmd->fd_aux[WRITE]), close(e->cmd->fd_aux[READ]));
        dispatch_command(e);
        exit(0);
    }
    if (e->file.input != 0)
        close(e->file.input);
    close(e->cmd->fd_aux[WRITE]);
    e->file.input = e->cmd->fd_aux[READ];
    return NULL;
}
static int *ft_exec_sec_cmd(t_exec *e)
{
    //	return (ft_print_error("pipe", 1, ""), NULL);
    e->cmd->pid = fork();
    if (e->cmd->pid < 0)
    {
        ft_print_error("fork", 1, "");
        return NULL;
    }
    else if (e->cmd->pid == 0)
    {
        if (dup2(e->file.input, STDIN_FILENO) == -1)
            (close(e->file.input), ft_print_error("dup2: ", 1, "input error"));
        if (e->file.input != 0)
            close(e->file.input);
        if (e->file.output != 1)
        {
            if (dup2(e->file.output, STDOUT_FILENO) == -1)
                (ft_print_error("dup2", 1, "output error"));
            close(e->file.output);
        }
        exit(dispatch_command(e)); // Finalizo con el estado del builtin sino
    }
    if (e->file.input != 0)
        close(e->file.input);
    if (e->file.output != 1)
        close(e->file.output);
    return NULL;
}

int *ft_exec_pipe(t_exec *e, int index)
{

    e = &e[index];
    char *p_heredoc;
    if (e->state[1] == 1)
    {
        ft_putstr_fd(">", STDOUT_FILENO);
        p_heredoc = get_next_line(STDIN_FILENO);
        p_heredoc = ft_strtrim(p_heredoc, "\n");
        e->cmd[1].cmd = do_exec(p_heredoc, e->handler->env);
    }
    if (e->state[0] == 0)
    {
        ft_exec(e);
        waitpid(e->cmd->pid, &e->cmd->status, 0); //NO debo esperar a todos una vez, debo esperar a todos al final.... PIPEX
        e->state[0] = WEXITSTATUS(e->cmd->status);
    }
    e->cmd++;
    if (e->state[1] == 0)
    {
        ft_exec_sec_cmd(e);
        waitpid(e->cmd->pid, &e->cmd->status, 0);
        e->state[1] = WEXITSTATUS(e->cmd->status);
    }

    e->status = e->state[1];
    return e->state;
}