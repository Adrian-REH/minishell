#include "../headers/minishell.h"

void ft_conf_pipe(t_handler *s, int i)
{

    s->exec[i].handler = s;
    s->exec[i].cmd = ft_calloc(sizeof(t_cmd), 3);
    s->exec[i].op = PIPE;
    s->exec[i].state = ft_calloc(sizeof(int), 2);
    s->exec[i].state[0] = 0;
    s->exec[i].state[1] = 0;
    s->exec[i].cmd[0].cmd = 0;
    if (s->info->oid != (i - 1))
    {
        s->exec[i].cmd[0].cmd = do_exec(s->info->tokens[i - 1], s->env);
        pipe(s->exec[i].cmd[0].fd_aux);
    }
    else
        s->exec[i].state[0] = 1;
    if (s->info->tokens[i + 1] && s->info->oid != (i + 1))
    {
        s->exec[i].cmd[1].cmd = do_exec(s->info->tokens[i + 1], s->env);
        pipe(s->exec[i].cmd[1].fd_aux);
    }
    else
        s->exec[i].state[1] = 1;
    s->exec[i].cmd[2].cmd = NULL;
    // s->info->oid = s->info->id + 1;
    //  Aqui debe llamar al resto de funciones para ejecutar el amp, y sus posibilidades
    s->exec[i].func[EMPTY][EMPTY] = ft_exec_pipe;
    s->info->oid = i + 1;
}