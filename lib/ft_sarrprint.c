#include "../src/headers/minishell.h"

int ft_sarrprint(char **arr)
{
    int i;

    if (!arr || !arr[0])
        return (0);
    i = -1;
    while (arr[++i])
        printf("%s\n", arr[i]);
    return (i);
}