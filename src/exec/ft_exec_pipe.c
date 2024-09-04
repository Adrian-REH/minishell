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
        printf("file.input: %d\n", e->file.input);
        if (dup2(e->file.input, STDIN_FILENO) == -1)
            (close(e->cmd->fd_aux[1]), close(e->cmd->fd_aux[0]), ft_print_error("dup2", 1, ""));
        if (e->file.input != 0)
            close(e->file.input);
        if (e->file.output != 1)
            close(e->file.output);
        printf("file.output: %d\n", e->cmd->fd_aux[WRITE]);
        if (dup2(e->cmd->fd_aux[WRITE], STDOUT_FILENO) == -1)
            (close(e->cmd->fd_aux[WRITE]), close(e->cmd->fd_aux[READ]), ft_print_error("dup2", 1, NULL));
        (close(e->cmd->fd_aux[WRITE]), close(e->cmd->fd_aux[READ]));
        if (execve(e->cmd->cmd[0], e->cmd->cmd, e->handler->env) == -1) // Se supone que ya se verifico que el path esta bien y que se puede ejecutar directamente.
            ft_print_error("command not found: ", 127, e->cmd->cmd[0]);
        exit(0);
    }
    if (e->file.input != 0)
        close(e->file.input);
    close(e->cmd->fd_aux[WRITE]);
    e->file.input = e->cmd->fd_aux[READ];
    return NULL;
}
static int *ft_exec_give_cmd(t_exec *e)
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

        printf("file.input: %d\n", e->file.input);
        if (dup2(e->file.input, STDIN_FILENO) == -1)
            (close(e->cmd->fd_aux[1]), close(e->cmd->fd_aux[0]), ft_print_error("dup2: ", 1, "input error"));
        if (e->file.input != 0)
            close(e->file.input);
        printf("file.output: %d\n", e->file.output);
        if (e->file.output != 1)
        {
            if (dup2(e->file.output, STDOUT_FILENO) == -1)
                (ft_print_error("dup2", 1, NULL));
            close(e->file.output);
        }
        if (execve(e->cmd->cmd[0], e->cmd->cmd, e->handler->env) == -1) // Se supone que ya se verifico que el path esta bien y que se puede ejecutar directamente.
            ft_print_error("command not found: ", 127, e->cmd->cmd[0]);
        exit(0);
    }
    if (e->file.input != 0)
        close(e->file.input);
    if (e->file.output != 1)
        close(e->file.output);

    return NULL;
}

int *ft_exec_pipe(t_exec *e)
{
    char *p_heredoc;
    printf("ft_exec_pipe: %d\n", e->state[1]);
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
        e->state[0] = WEXITSTATUS(e->cmd[0].pid);
    }
    e->cmd++;

    ft_exec_give_cmd(e);
    waitpid(e->cmd->pid, &e->cmd->status, 0);
    e->state[1] = WEXITSTATUS(e->cmd->status);

    if (e->state[1] != 0 || e->state[1] != 0)
        e->status = -1;
    e->file.input = e->cmd->fd_aux[READ];
    e->file.output = e->cmd->fd_aux[WRITE];
    return e->state;
}