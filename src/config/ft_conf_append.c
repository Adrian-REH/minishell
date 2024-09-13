#include "../headers/minishell.h"

void ft_conf_append(t_handler *s, int i)
{
    char *line;
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
    exec[k].handler = s;
    exec[k].cmd = ft_calloc(sizeof(t_cmd), 3);
    exec[k].op = APPEND;
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
        exec[k].cmd[0].cmd = sarr_clean_quote(exec[k].cmd[0].cmd);
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

    // Transferir los APPEND y GREATER A la ultima ejecucion
    while (exec[--j].op == APPEND || exec[j].op == GREATER)
    {
        if (exec[j].state[0] == 0)
        {
            exec[k].cmd[0].line = exec[j].cmd[0].line;
            exec[k].cmd[0].cmd = exec[j].cmd[0].cmd;
            exec[k].cmd[0].fd_aux[0] = (exec[j].cmd[0].fd_aux[0]);
            exec[k].cmd[0].fd_aux[1] = (exec[j].cmd[0].fd_aux[1]);
            exec[k].state[0] = 0;
            exec[j].state[0] = 1; // Anulo para que no se ejecute el comando
        }
    }
    exec[k].cmd[1].cmd = NULL;
    // Aqui debe llamar al resto de funciones para ejecutar el amp, y sus posibilidades
    exec[k].func[0][0] = ft_exec_append;
    s->info->oid = i + 1;
    if (s->block[s->info->i].isnext)
        b->len_exec_next++;
    else
        b->len_exec_prev++;
}