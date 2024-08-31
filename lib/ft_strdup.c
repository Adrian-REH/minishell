#include "../src/headers/minishell.h"

char *ft_strdup(const char *str)
{
    size_t len;
    char *temp;

    len = ft_strlen(str);
    temp = (char *)malloc(sizeof(char) * (len + 1));
    if (!temp)
        return (NULL);
    ft_strlcpy(temp, (char *)str, len + 1);
    return (temp);
}