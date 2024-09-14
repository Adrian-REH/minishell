#include "../src/headers/minishell.h"

char *ft_strdelchr(char *str, char c)
{
    int i;
    int j;

    if (!str)
        return NULL;

    i = 0;
    while (str[i])
    {
        if (str[i] == c)
        {
            j = i;
            while (str[j])
            {
                str[j] = str[j + 1]; 
                j++;
            }
        }
        else
            i++;
    }
    return (str);
}
