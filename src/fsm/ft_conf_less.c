#include "../headers/minishell.h"

void ft_conf_less(t_handler *s, int i)
{
    char *line;
    int j = s->info->i;
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
    // int fd;
    exec[k].handler = s;
    exec[k].cmd = ft_calloc(sizeof(t_cmd), 3);
    exec[k].op = LESS;
    exec[k].state = ft_calloc(sizeof(int), 2);
    exec[k].state[0] = 0;
    exec[k].state[1] = 0;
    exec[k].cmd[0].cmd = 0;
    exec[k].file.input = 0;
    exec[k].file.output = 1;
    if (s->info->oid != (i - 1))
    {
        exec[k].cmd[0].line = s->info->tokens[i - 1];
        exec[k].cmd[0].cmd = do_exec(s->info->tokens[i - 1], s->env);
        pipe(exec[k].cmd[0].fd_aux);
    }
    else
        exec[k].state[0] = 1;
    if (s->info->oid != (i + 1))
    {
        line = s->info->tokens[i + 1];
        line = ft_strtrim(line, "\"");
        exec[k].file.dir_file = line; // Tengo que liberar la linea
        exec[k].state[1] = 0;
    }
    else
        exec[k].state[1] = 1;

    while (exec[--j].op == LESS)
    {
        if (exec[j].state[0] == 0)
        {
            exec[k].cmd[0].line = exec[j].cmd[0].line;
            exec[k].cmd[0].cmd = exec[j].cmd[0].cmd;
            exec[k].cmd[0].fd_aux[0] = (exec[j].cmd[0].fd_aux[0]);
            exec[k].cmd[0].fd_aux[1] = (exec[j].cmd[0].fd_aux[1]);
            exec[k].state[0] = 0;
        }
    }
    s->info->oid = i + 1;
    exec[k].cmd[2].cmd = NULL;
    // En caso de que los dos estados o uno solo no se pueda ejecutar deberia devolver un error, por tanto llamar a otra funcion
    exec[k].func[0][0] = ft_exec_less;

    if (s->block[s->info->i].isnext)
        b->len_exec_next++;
    else
        b->len_exec_prev++;
}
