#include "../headers/minishell.h"

void ft_conf_cmd(t_handler *s, int i)
{
    s->exec[s->info->i].state = ft_calloc(sizeof(int), 2);
    s->exec[s->info->i].state[0] = 0;
    s->exec[s->info->i].state[1] = 0;
    s->exec[s->info->i].cmd = malloc(sizeof(t_cmd));
    s->exec[s->info->i].cmd->handler = s;
    s->exec[s->info->i].cmd->line = s->info->tokens[i];
    s->exec[s->info->i].cmd->cmd = do_exec(s->info->tokens[i], s->env);
    s->exec[s->info->i].op = UNIQ_COMMAND;
    pipe(s->exec[s->info->i].cmd->fd_aux);
    s->info->oid = i;
    s->exec[s->info->i].func[0][0] = ft_exec_cmd;
    s->info->i++;
}