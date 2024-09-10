#include "../headers/minishell.h"

void ft_conf_pipe(t_handler *s, int i)
{

    s->exec[s->info->i].handler = s;
    s->exec[s->info->i].cmd = ft_calloc(sizeof(t_cmd), 3);
    s->exec[s->info->i].op = PIPE;
    s->exec[s->info->i].state = ft_calloc(sizeof(int), 2);
    s->exec[s->info->i].state[0] = 0;
    s->exec[s->info->i].state[1] = 0;
    s->exec[s->info->i].cmd[0].cmd = 0;
    if (s->info->oid != (i - 1))
    {
        s->exec[s->info->i].cmd[0].status = 0;
        s->exec[s->info->i].cmd[0].line = s->info->tokens[i - 1];
        s->exec[s->info->i].cmd[0].cmd = do_exec(s->info->tokens[i - 1], s->env);
        pipe(s->exec[s->info->i].cmd[0].fd_aux);
    }
    else
        s->exec[s->info->i].state[0] = 1;
    if (strcmp(s->info->tokens[i + 1], " ") && s->info->oid != (i + 1))
    {
        s->exec[s->info->i].cmd[1].status = 0;
        s->exec[s->info->i].cmd[1].line = s->info->tokens[i + 1];
        s->exec[s->info->i].cmd[1].cmd = do_exec(s->info->tokens[i + 1], s->env);
        // pipe(s->exec[s->info->i].cmd[1].fd_aux);
    }
    else
        s->exec[s->info->i].state[1] = 1;
    s->exec[s->info->i].cmd[2].cmd = NULL;
    //  Aqui debe llamar al resto de funciones para ejecutar el amp, y sus posibilidades
    s->exec[s->info->i].func[EMPTY][EMPTY] = ft_exec_pipe;
    s->info->oid = i + 1;
    s->info->i++;
}