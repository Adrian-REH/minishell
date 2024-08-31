#include "../src/headers/minishell.h"

size_t ft_strlcpy(char *dest, char *src, size_t size)
{
    size_t j;

    if (size == 0)
        return (ft_strlen(src));
    j = 0;
    while (src[j] != '\0' && j < size - 1)
    {
        dest[j] = src[j];
        j++;
    }
    dest[j] = '\0';
    return (ft_strlen(src));
}