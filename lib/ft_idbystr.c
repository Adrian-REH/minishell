#include "../src/headers/minishell.h"

int idstr(char *alphabet[], char *str)
{
    int i;

    i = -1;
    if (strcmp(str, " ") == 0)
        return (0);
    while (alphabet[++i])
        if (strcmp(alphabet[i], str) == 0)
            return (i);
    return (NOT_OPERATOR);
}