#include "../headers/minishell.h"

void ft_conf_less(t_handler *s, int i)
{
    s->exec[i].cmd = malloc(sizeof(t_cmd) * (3));
    s->exec[i].op = LESS;
    s->exec[i].cmd[0].cmd = ft_split(s->info->tokens[i - 1], ' ');
    pipe(s->exec[i].cmd[0].fd_aux);
    s->exec[i].cmd[1].cmd = ft_split(s->info->tokens[i + 1], ' ');
    pipe(s->exec[i].cmd[1].fd_aux);
    s->exec[i].cmd[2].cmd = NULL;
    // Aqui debe llamar al resto de funciones para ejecutar el amp, y sus posibilidades
    // s->exec[i].func = ft_exec_amper;
}