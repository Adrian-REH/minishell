#include "../src/headers/minishell.h"

void ft_bzero(void *str, size_t n)
{
    size_t i;

    i = -1;
    while (++i < n)
        ((unsigned char *)str)[i] = '\0';
}