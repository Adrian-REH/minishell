#include "../headers/minishell.h"

void ft_conf_greater(t_handler *s, int i)
{
    printf("conf greater\n");
    s->exec[i].cmd = malloc(sizeof(t_cmd) * (2));
    s->exec[i].op = GREATER;
    s->exec[i].state = ft_calloc(sizeof(int), 2);
    s->exec[i].state[0] = 0;
    s->exec[i].state[1] = 0;
    s->exec[i].cmd[0].cmd = do_exec(s->info->tokens[i - 1], s->env);
    pipe(s->exec[i].cmd[0].fd_aux);
    s->exec[i].file.output = open(s->info->tokens[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
    s->exec[i].cmd[1].cmd = NULL;
    // Aqui debe llamar al resto de funciones para ejecutar el amp, y sus posibilidades
    s->exec[i].func[0][0] = ft_exec_greater;
}