#include "../headers/minishell.h"
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
        //printf("cmd: %s\n", e->cmd->line);
        //printf("file.input: %d\n", e->file.input);
        if (dup2(e->file.input, STDIN_FILENO) == -1)
            (close(e->cmd->fd_aux[1]), close(e->cmd->fd_aux[0]), ft_print_error("dup2: ", 1, "input error"));
        if (e->file.input != 0)
            close(e->file.input);
        //printf("file.output: %d\n", e->file.output);
        if (e->file.output != 1)
        {
            if (dup2(e->file.output, STDOUT_FILENO) == -1)
                (ft_print_error("dup2", 1, NULL));
            close(e->file.output);
        }
        dispatch_command(e);
        exit(0);
    }
    if (e->file.input != 0)
        close(e->file.input);
    if (e->file.output != 1)
        close(e->file.output);

    return NULL;
}
static void ft_heredoc(t_exec *e)
{
    char *p_heredoc;
    int status;

    status = 0;
    e->cmd->pid = fork();
    if (e->cmd->pid == -1)
        ft_print_error("fork", 1, "");
    else if (e->cmd->pid == 0)
    {
        close(e->cmd->fd_aux[READ]);
        //printf("file.input: %d\n", e->file.input);
        //printf("file.output: %d\n", e->file.output);
        while (1)
        {
            ft_putstr_fd("heredoc>", STDOUT_FILENO);
            p_heredoc = get_next_line(0);
            // ft_putstr_fd(p_heredoc, STDOUT_FILENO);
            // ft_putstr_fd(e->file.end_heredoc, STDOUT_FILENO);
            if (ft_strcmp(e->file.end_heredoc, p_heredoc) == 0)
            {
                (free(p_heredoc), close(e->cmd->fd_aux[WRITE]), exit(0));
            }
            (ft_putstr_fd(p_heredoc, e->cmd->fd_aux[WRITE]), free(p_heredoc));
        }
    }
    else
        waitpid(e->cmd->pid, &status, 0);
    e->cmd->status = WEXITSTATUS(status);
    close(e->cmd->fd_aux[WRITE]);
    e->file.input = e->cmd->fd_aux[READ];
}
int *ft_exec_heredoc(t_exec *e)
{
    printf("ft_exec_heredoc\n");
    ft_heredoc(e);
    e->cmd++;
    ft_exec_give_cmd(e);
    waitpid(e->cmd->pid, &e->cmd->status, 0);
    e->state[1] = WEXITSTATUS(e->cmd->status);
    if (e->state[1] != 0 || e->state[1] != 0)
        e->status = -1;
    e->file.input = e->cmd->fd_aux[READ];
    e->file.output = e->cmd->fd_aux[WRITE];
    e->handler->code = e->state[1];
    return e->state;
}