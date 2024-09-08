#include "../headers/minishell.h"

void ft_conf_heredoc(t_handler *s, int i)
{
    s->exec[s->info->i].cmd = ft_calloc(sizeof(t_cmd), 3);
    s->exec[s->info->i].op = HEREDOC;
    s->exec[s->info->i].state = ft_calloc(sizeof(int), 2);
    s->exec[s->info->i].state[0] = 0;
    s->exec[s->info->i].state[1] = 0;
    if (s->info->oid != (i - 1))
    {
        s->exec[s->info->i].cmd[1].line = s->info->tokens[i - 1];
        s->exec[s->info->i].cmd[1].cmd = do_exec(s->info->tokens[i - 1], s->env);
        pipe(s->exec[s->info->i].cmd[1].fd_aux);
    }
    else
        s->exec[s->info->i].state[1] = 1;

    s->exec[s->info->i].file.end_heredoc = ft_strjoin(s->info->tokens[i + 1], "\n");
    pipe(s->exec[s->info->i].cmd[0].fd_aux);

    s->info->oid = i + 1;
    // s->exec[s->info->i].cmd[2].cmd = NULL;
    // Aqui debe llamar al resto de funciones para ejecutar el amp, y sus posibilidades
    s->exec[s->info->i].func[0][0] = ft_exec_heredoc;
    // s->exec[s->info->i].func[1] = handler_except;
    // s->exec[s->info->i].func[2] = next_process;
    s->info->i++;
}
