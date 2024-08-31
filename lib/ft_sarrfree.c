#include "../src/headers/minishell.h"

void ft_sarrfree(char ***arr)
{
    int i;

    if (!arr || !arr[0])
        return;
    i = -1;
    while (arr[0][++i])
    {
        if (arr[0][i])
        {
            free(arr[0][i]);
            arr[0][i] = NULL;
        }
    }
    free(*arr);
    *arr = NULL;
}