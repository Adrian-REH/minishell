#include "../src/headers/minishell.h"

int ft_sarrprint(char **arr)
{
    int i;

    if (!arr || !arr[0])
        return (0);
    i = -1;
    while (arr[++i])
    {
        ft_putstr_fd(arr[i], 1);
        ft_putstr_fd("\n", 1);
    }
    return (i);
}