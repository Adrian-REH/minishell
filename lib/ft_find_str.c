#include "../src/headers/minishell.h"

char *find_str(char *str, char **env)
{
    int i;
    int j;
    char *sub;

    i = 0;
    j = 0;
    while (env[i])
    {
        j = 0;
        while (env[i][j] && env[i][j] != '=')
            j++;
        sub = ft_substr(env[i], 0, j);
        if (ft_strncmp(sub, str, ft_strlen(str)) == 0)
            return (free(sub), (env[i] + j + 1));
        i += (free(sub), 1);
    }
    return (NULL);
}