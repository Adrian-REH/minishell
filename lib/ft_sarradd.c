#include "../src/headers/minishell.h"
char **ft_sarradd(char **arr, char *string)
{
    int size;
    char **new_arr;

    if (!string)
        return (arr);
    size = ft_sarrsize(arr) + 2;
    new_arr = malloc(sizeof(char *) * (size));
    size = 0;
    if (arr)
    {
        while (arr[size])
        {
            new_arr[size] = ft_strdup(arr[size]);
            size++;
        }
        ft_sarrfree(&arr);
    }
    new_arr[size++] = ft_strdup(string);
    new_arr[size] = NULL;
    return (new_arr);
}