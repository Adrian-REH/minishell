#include "../headers/minishell.h"

void ft_conf_heredoc(t_handler *s, int i)
{
    printf("ft_conf_heredoc\n");
    int j = s->info->i;
    s->exec[s->info->i].cmd = ft_calloc(sizeof(t_cmd), 3);
    s->exec[s->info->i].op = HEREDOC;
    s->exec[s->info->i].state = ft_calloc(sizeof(int), 2);
    s->exec[s->info->i].state[0] = 0;
    s->exec[s->info->i].state[1] = 0;
    s->exec[s->info->i].file.input = 0;
    s->exec[s->info->i].file.output = 1;
    if (s->info->oid != (i - 1))
    {
        s->exec[s->info->i].cmd[1].line = s->info->tokens[i - 1];
        s->exec[s->info->i].cmd[1].cmd = do_exec(s->info->tokens[i - 1], s->env);
        pipe(s->exec[s->info->i].cmd[1].fd_aux);
    }
    else
        s->exec[s->info->i].state[1] = 1;

    // Transferir los heredocs
    while (s->exec[--j].op == HEREDOC)
    {
        s->exec[s->info->i].cmd[1].line = s->exec[j].cmd[1].line;
        s->exec[s->info->i].cmd[1].cmd = s->exec[j].cmd[1].cmd;
        s->exec[s->info->i].cmd[1].fd_aux[0] = (s->exec[j].cmd[1].fd_aux[0]);
        s->exec[s->info->i].cmd[1].fd_aux[1] = (s->exec[j].cmd[1].fd_aux[1]);
        s->exec[j].state[1] = 1;
        s->exec[s->info->i].state[1] = 0;
    }
    s->exec[s->info->i].file.end_heredoc = ft_strjoin(s->info->tokens[i + 1], "\n");
    pipe(s->exec[s->info->i].cmd[0].fd_aux);

    s->exec[s->info->i].func[0][0] = ft_exec_heredoc;
    s->info->oid = i + 1;
    s->info->i++;
}
