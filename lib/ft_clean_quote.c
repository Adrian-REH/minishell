#include "../src/headers/minishell.h"

char **sarr_clean_quote(char **arr)
{
    int i;
    char *line;

    i = -1;
    while (arr[++i])
    {
        line = ft_strtrim(arr[i], "\"");
        free(arr[i]);
        arr[i] = line;
    }
    return (arr);
}