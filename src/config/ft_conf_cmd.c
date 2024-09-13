#include "../headers/minishell.h"

void ft_conf_cmd(t_handler *s, int i)
{
    int k;
    t_exec *exec;
    t_block *b;

    b = &(s->block[s->info->i]);
    if (s->block[s->info->i].isnext)
    {
        k = b->len_exec_next;
        exec = b->next_exec;
    }
    else
    {
        k = b->len_exec_prev;
        exec = b->prev_exec;
    }
    exec[k].state = ft_calloc(sizeof(int), 2);
    exec[k].state[0] = 0;
    exec[k].state[1] = 0;
    exec[k].cmd = malloc(sizeof(t_cmd));
    exec[k].cmd->handler = s;
    exec[k].cmd->line = s->info->tokens[i];
    exec[k].file.input = 0;
    exec[k].file.output = 1;
    // if (ft_strchr(s->info->tokens[i], '$') && ft_isalpha(ft_strchr(s->info->tokens[i], '$')[1]))
    //     s->exec[s->info->i].cmd->line = ft_getenv(s->exec[s->info->i].cmd, s->info->tokens[i] + 1);
    exec[k].cmd->cmd = do_exec(exec[k].cmd->line, s->env);
    exec[k].cmd->cmd = sarr_clean_quote(exec[k].cmd->cmd);
    exec[k].op = UNIQ_COMMAND;
    // pipe(s->exec[s->info->i].cmd->fd_aux);
    s->info->oid = i;
    exec[k].func[0][0] = ft_exec_cmd;

    if (s->block[s->info->i].isnext)
    {
        s->block[s->info->i].len_exec_next++;
    }
    else
    {
        s->block[s->info->i].len_exec_prev++;
    }
    // s->info->i++;
}