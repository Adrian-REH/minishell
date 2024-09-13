#include "../headers/minishell.h"

void ft_conf_and(t_handler *s, int i)
{
    (void)i;
    s->block[s->info->i].op = BLOCK_AND;
    if (s->block[s->info->i].len_exec_next > 0)
    {
        s->info->i++;
        printf("ft_conf_and: %d\n", s->info->i);
        s->block[s->info->i].isnext = 0;
        s->block[s->info->i].len_exec_prev = 0;
        s->block[s->info->i].len_exec_next = 0;
        s->block[s->info->i].next_exec = 0;
        s->block[s->info->i].len_exec = 0;
        s->block[s->info->i].prev_exec = 0;
    }
    else
        s->block[s->info->i].isnext = 1;
}