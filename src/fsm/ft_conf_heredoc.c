#include "../headers/minishell.h"

void ft_conf_heredoc(t_handler *s, int i)
{
    s->exec[i].cmd = malloc(sizeof(t_cmd));
    s->exec[i].op = HEREDOC;
    s->exec[i].cmd->cmd = ft_split(s->info->tokens[i - 1], ' ');
    s->exec[i].file.end_heredoc = ft_strjoin(s->info->tokens[i + 1], "\n");
    pipe(s->exec[i].file.fd_aux);
    // s->exec[i].cmd[2].cmd = NULL;
    // Aqui debe llamar al resto de funciones para ejecutar el amp, y sus posibilidades
    s->exec[i].func[0][0] = ft_exec_heredoc;
    // s->exec[i].func[1] = handler_except;
    // s->exec[i].func[2] = next_process;
}
