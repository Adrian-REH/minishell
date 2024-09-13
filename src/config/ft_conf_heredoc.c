#include "../headers/minishell.h"

void ft_conf_heredoc(t_handler *s, int i)
{
    printf("ft_conf_heredoc\n");
    int j;
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

    j = k;
    exec[k].cmd = ft_calloc(sizeof(t_cmd), 3);
    exec[k].op = HEREDOC;
    exec[k].state = ft_calloc(sizeof(int), 2);
    exec[k].state[0] = 0;
    exec[k].state[1] = 0;
    exec[k].file.input = 0;
    exec[k].file.output = 1;
    if (s->info->oid != (i - 1))
    {
        exec[k].cmd[1].line = s->info->tokens[i - 1];
        exec[k].cmd[1].cmd = do_exec(s->info->tokens[i - 1], s->env);
        exec[k].cmd[1].cmd = sarr_clean_quote(exec[k].cmd[1].cmd);
        pipe(exec[k].cmd[1].fd_aux);
    }
    else
        exec[k].state[1] = 1;

    // Transferir los heredocs
    while (exec[--j].op == HEREDOC || exec[j].op == LESS)
    {
        exec[k].cmd[1].line = exec[j].cmd[1].line;
        exec[k].cmd[1].cmd = exec[j].cmd[1].cmd;
        exec[k].cmd[1].fd_aux[0] = (exec[j].cmd[1].fd_aux[0]);
        exec[k].cmd[1].fd_aux[1] = (exec[j].cmd[1].fd_aux[1]);
        exec[j].state[1] = 1;
        exec[k].state[1] = 0;
    }
    exec[k].file.end_heredoc = ft_strjoin(s->info->tokens[i + 1], "\n");
    pipe(exec[k].cmd[0].fd_aux);

    exec[k].func[0][0] = ft_exec_heredoc;
    s->info->oid = i + 1;

    if (s->block[s->info->i].isnext)
        b->len_exec_next++;
    else
        b->len_exec_prev++;
}
