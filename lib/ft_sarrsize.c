#include "../src/headers/minishell.h"
int ft_sarrsize(char **arr)
{
    int size;

    if (!arr)
        return (0);
    size = 0;
    while (arr[size])
        size++;
    return (size);
}