#include "../headers/minishell.h"

void ft_conf_cmd(t_handler *s, int i)
{
    i++;
    s->exec[i].state = ft_calloc(sizeof(int), 2);
    s->exec[i].state[0] = 0;
    s->exec[i].state[1] = 0;
    s->exec[i].cmd = malloc(sizeof(t_cmd));
    s->exec[i].cmd->cmd = do_exec(s->info->tokens[i], s->env);
    s->exec[i].op = UNIQ_COMMAND;
    pipe(s->exec[i].cmd->fd_aux);
    // Aqui debe llamar al resto de funciones para ejecutar el amp, y sus posibilidades
    s->info->oid = s->info->id + 1;
    s->exec[i].func[0][0] = ft_exec_cmd;
}