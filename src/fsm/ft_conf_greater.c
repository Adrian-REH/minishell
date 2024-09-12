#include "../headers/minishell.h"

void ft_conf_greater(t_handler *s, int i)
{
    char *line;
    int j = s->info->i;
    s->exec[s->info->i].handler = s;
    s->exec[s->info->i].cmd = ft_calloc(sizeof(t_cmd), 3);
    s->exec[s->info->i].op = GREATER;
    s->exec[s->info->i].state = ft_calloc(sizeof(int), 2);
    s->exec[s->info->i].state[0] = 0;
    s->exec[s->info->i].state[1] = 0;
    s->exec[s->info->i].cmd[0].cmd = 0;
    s->exec[s->info->i].file.input = 0;
    s->exec[s->info->i].file.output = 1;
    if (s->info->oid != (i - 1))
    {
        s->exec[s->info->i].cmd[0].line = s->info->tokens[i - 1];
        s->exec[s->info->i].cmd[0].cmd = do_exec(s->info->tokens[i - 1], s->env);
        pipe(s->exec[s->info->i].cmd[0].fd_aux);
    }
    else
        s->exec[s->info->i].state[0] = 1;
    if (s->info->oid != (i + 1))
    {
        line = s->info->tokens[i + 1];
        line = ft_strtrim(line, "\"");
        s->exec[s->info->i].file.dir_file = line; // Tengo que liberar la linea
        s->exec[s->info->i].file.output = open(line, O_WRONLY | O_CREAT, 0777);
        s->exec[s->info->i].state[1] = 0;
    }
    else
        s->exec[s->info->i].state[1] = 1;
    while (s->exec[--j].op == GREATER)
    {
        s->exec[j].file.dir_file = s->exec[s->info->i].file.dir_file;
    }
    s->exec[s->info->i].cmd[1].cmd = NULL;
    s->info->oid = i + 1;
    // Aqui debe llamar al resto de funciones para ejecutar el amp, y sus posibilidades
    if (s->exec[s->info->i - 1].op != GREATER)
        s->exec[s->info->i].func[0][0] = ft_exec_greater;
    s->info->i++;
}