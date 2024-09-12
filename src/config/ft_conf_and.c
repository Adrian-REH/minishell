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

    // s->exec[s->info->i].blocks[j].prev_exec = s->block[s->info->i].prev_exec;

    /*     s->exec[s->info->i].cmd = (t_cmd *)ft_calloc(sizeof(t_cmd), 3);
        s->exec[s->info->i].state = ft_calloc(sizeof(int), 2);
        s->exec[s->info->i].state[0] = 0;
        s->exec[s->info->i].state[1] = 0;
        s->exec[s->info->i].file.input = 0;
        s->exec[s->info->i].file.output = 1;
        if (s->info->oid != (i - 1))
        {
            s->exec[s->info->i].cmd[0].handler = s;
            s->exec[s->info->i].cmd[0].line = s->info->tokens[i - 1];
            s->exec[s->info->i].cmd[0].cmd = do_exec(s->info->tokens[i - 1], s->env);
            pipe(s->exec[s->info->i].cmd[0].fd_aux);
        }
        else
            s->exec[s->info->i].state[0] = 1;
        if (strcmp(s->info->tokens[i + 1], " ") && s->info->oid != (i + 1)) // todo el estado dle anterior comando
        {
            s->exec[s->info->i].cmd[1].handler = s;
            s->exec[s->info->i].cmd[1].line = s->info->tokens[i + 1];
            s->exec[s->info->i].cmd[1].cmd = do_exec(s->info->tokens[i + 1], s->env);
            pipe(s->exec[s->info->i].cmd[1].fd_aux);
        }
        else
            s->exec[s->info->i].state[1] = 1;
        s->info->oid = i + 1;
        s->exec[s->info->i].func[0][0] = ft_exec_and; */
}