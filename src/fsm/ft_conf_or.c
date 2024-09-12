#include "../headers/minishell.h"

void ft_conf_or(t_handler *s, int i)
{
    (void)i;
    s->block[s->info->i].op = BLOCK_OR;
    if (s->block[s->info->i].len_exec_next > 0)
    {
        s->info->i++;
        s->block[s->info->i].isnext = 0;
        s->block[s->info->i].len_exec_prev = 0;
        s->block[s->info->i].len_exec_next = 0;
        s->block[s->info->i].next_exec = 0;
        s->block[s->info->i].len_exec = 0;
        s->block[s->info->i].prev_exec = 0;
    }
    else
        s->block[s->info->i].isnext = 1;

    // s->exec[s->info->i].func[0][1] = ft_finish;
}