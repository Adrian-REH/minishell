#include "../headers/minishell.h"

void ft_conf_and(t_handler *s, int i)
{
    s->exec[i].cmd = ft_calloc(sizeof(t_cmd), 3);
    s->exec[i].op = AND;
    if (strcmp(s->info->last_cmd, s->info->tokens[i - 1]) != 0)
    {

        s->exec[i].cmd[0].cmd = do_exec(s->info->tokens[i - 1], s->env);
        pipe(s->exec[i].cmd[0].fd_aux);
    }
    if (strcmp(s->info->last_cmd, s->info->tokens[i + 1]) != 0)
    {
        s->exec[i].cmd[1].cmd = do_exec(s->info->tokens[i + 1], s->env);
        pipe(s->exec[i].cmd[1].fd_aux);
    }
    s->info->last_cmd = s->info->tokens[i + 1];
    s->exec[i].func[0][0] = ft_exec_and;
    // s->exec[i].func[0][1] = ft_finish;
}