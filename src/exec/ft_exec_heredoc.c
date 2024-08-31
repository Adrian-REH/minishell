#include "../headers/minishell.h"
int *ft_exec_heredoc(t_exec *e)
{
    char *p_heredoc;
    int status;

    status = 0;
    e->cmd->pid = fork();
    if (e->cmd->pid == -1)
        ft_print_error("fork", 1, "");
    else if (e->cmd->pid == 0)
    {
        close(e->file.fd_aux[READ]);
        while (1)
        {
            ft_putstr_fd("heredoc>", STDOUT_FILENO);
            p_heredoc = get_next_line(0);
            ft_putstr_fd(p_heredoc, STDOUT_FILENO);
            ft_putstr_fd(e->file.end_heredoc, STDOUT_FILENO);

            if (ft_strcmp(e->file.end_heredoc, p_heredoc) == 0)
            {
                (free(p_heredoc), close(e->file.fd_aux[WRITE]), exit(0));
            }
            (ft_putstr_fd(p_heredoc, e->file.fd_aux[WRITE]), free(p_heredoc));
        }
    }
    else
        waitpid(e->cmd->pid, &status, 0);
    e->cmd->status = WEXITSTATUS(status);

    // Busca la siguiente cosa que hacer
    e->state[0] = e->state[1];
    e->state[1] = e->cmd->status;
    return e->state;
}