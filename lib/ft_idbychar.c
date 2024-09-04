#include "../src/headers/minishell.h"

int idx(char *alphabet[], char c)
{
    int i;

    i = -1;
    while (alphabet[++i])
        if (ft_chrpos(alphabet[i], c, 0) != -1)
            return (i);
    return (i);
}