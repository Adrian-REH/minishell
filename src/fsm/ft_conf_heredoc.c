#include "../headers/minishell.h"

void ft_conf_heredoc(t_handler *s, int i)
{
    s->exec[i].cmd = ft_calloc(sizeof(t_cmd), 3);
    s->exec[i].op = HEREDOC;
    s->exec[i].state = ft_calloc(sizeof(int), 2);
    s->exec[i].state[0] = 0;
    s->exec[i].state[1] = 0;
    if (s->info->oid != (i - 1))
    {
        s->exec[i].cmd[1].cmd = do_exec(s->info->tokens[i - 1], s->env);
        pipe(s->exec[i].cmd[1].fd_aux);
    }
    else
        s->exec[i].state[1] = 1;

    s->exec[i].file.end_heredoc = ft_strjoin(s->info->tokens[i + 1], "\n");
    pipe(s->exec[i].cmd[0].fd_aux);

    s->info->oid = i + 1;
    // s->exec[i].cmd[2].cmd = NULL;
    // Aqui debe llamar al resto de funciones para ejecutar el amp, y sus posibilidades
    s->exec[i].func[0][0] = ft_exec_heredoc;
    // s->exec[i].func[1] = handler_except;
    // s->exec[i].func[2] = next_process;
}
