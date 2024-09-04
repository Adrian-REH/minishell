#include "../src/headers/minishell.h"

void ft_free_p2(char **dst)
{
    size_t n_word;

    n_word = 0;
    while (dst[n_word])
        free(dst[n_word++]);
    free(dst);
}
char *get_path(char *command, char **env)
{
    int i;
    char **path_env;
    char *path_part;
    char *exec;

    i = 0;
    path_env = ft_split(find_str("PATH", env), ':');
    if (!path_env)
        return (NULL);
    while (path_env[++i])
    {
        path_part = ft_strjoin(path_env[i], "/");
        exec = ft_strjoin(path_part, command);
        free(path_part);
        if (access(exec, F_OK | X_OK) == 0)
            return (ft_free_p2(path_env), exec);
        free(exec);
    }
    return (ft_free_p2(path_env), command);
}