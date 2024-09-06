#include "../headers/minishell.h"

/**
 * @file service_exception.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-09-06
 *
 * @copyright Copyright (c) 2024
 *
 * Aqui deberia estar todas las funciones de excepciones, y su arquitectura.
 */

void token_exception(t_automata *a, void *data)
{
    (void)a;
    (void)data;
}

void ft_conf_exception(t_handler *s, int i)
{
    (void)s;
    (void)i;
    s->code = 2;
}

void ft_execute_exception(t_cmd *cmd)
{
    (void)cmd;
}