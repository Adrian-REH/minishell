#include "../headers/minishell.h"

void ft_conf_less(t_handler *s, int i)
{
    printf("ft_conf_less\n");
    s->exec[i].handler = s;
    s->exec[i].cmd = ft_calloc(sizeof(t_cmd), 3);
    s->exec[i].op = LESS;
    s->exec[i].state = ft_calloc(sizeof(int), 2);
    s->exec[i].state[0] = 0;
    s->exec[i].state[1] = 0;
    s->exec[i].cmd[0].cmd = 0;
    if (s->info->oid != (i - 1))
    {
        s->exec[i].cmd[0].cmd = do_exec(s->info->tokens[i - 1], s->env);
        pipe(s->exec[i].cmd[0].fd_aux);
    }
    else
        s->exec[i].state[0] = 1;
    if (s->info->oid != (i + 1))
    {
        s->exec[i].file.input = open(s->info->tokens[i + 1], O_WRONLY, 0777);
        s->exec[i].state[1] = 0;
    }
    else
        s->exec[i].state[1] = 1;
    s->info->oid = i + 1;
    s->exec[i].cmd[2].cmd = NULL;
    // Aqui debe llamar al resto de funciones para ejecutar el amp, y sus posibilidades
    s->exec[i].func[0][0] = ft_exec_less;
}
