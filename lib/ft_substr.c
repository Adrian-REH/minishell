#include "../src/headers/minishell.h"

char *ft_substr(const char *str, unsigned int start, size_t len)
{
    char *temp;
    unsigned int i;

    if (!str)
        return (NULL);
    if (start > (unsigned int)ft_strlen(str) || !*str)
        return (ft_strdup(""));
    if (ft_strlen(str) + 1 <= (int)(len + start))
        len = ft_strlen(str) - start;
    temp = calloc(sizeof(char), len + 1);
    if (!temp)
        return (NULL);
    i = -1;
    while (++i < len)
        temp[i] = str[start + i];
    return (temp);
}