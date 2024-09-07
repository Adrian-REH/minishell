#include "../headers/minishell.h"

void ft_conf_or(t_handler *s, int i)
{
    s->exec[i].cmd = ft_calloc(sizeof(t_cmd), 3);
    s->exec[i].op = OR;
    s->exec[i].state = ft_calloc(sizeof(int), 2);
    s->exec[i].state[0] = 0;
    s->exec[i].state[1] = 0;
    if (s->info->oid != (i - 1))
    {
        s->exec[i].cmd[0].line = s->info->tokens[i - 1];
        s->exec[i].cmd[0].cmd = do_exec(s->info->tokens[i - 1], s->env);
        pipe(s->exec[i].cmd[0].fd_aux);
    }
    else
        s->exec[i].state[0] = 1;
    if (strcmp(s->info->tokens[i + 1], " ") && s->info->oid != (i + 1)) // todo el estado dle anterior comando
    {
        s->exec[i].cmd[0].line = s->info->tokens[i + 1];
        s->exec[i].cmd[1].cmd = do_exec(s->info->tokens[i + 1], s->env);
        pipe(s->exec[i].cmd[1].fd_aux);
    }
    else
        s->exec[i].state[1] = 1;
    s->info->oid = i + 1;

    s->exec[i].func[0][0] = ft_exec_or;
    // s->exec[i].func[0][1] = ft_finish;
}