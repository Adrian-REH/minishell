
#include "../headers/minishell.h"

void ft_free_p2(char **dst)
{
    size_t n_word;

    n_word = 0;
    while (dst[n_word])
        free(dst[n_word++]);
    free(dst);
}
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

char **do_exec(char *line, char **env)
{
    char *cmd;
    char **command;

    command = ft_split(line, ' ');
    if (!command)
        return (perror("Memory error: "), NULL);
    if (*command == 0)
        return (ft_free_p2(command), NULL);
    if ((access(command[0], F_OK | X_OK) == 0) && ft_strnstr(command[0], "./", 2))
        return (command);
    else if (access(command[0], F_OK | X_OK) != 0 && ft_strchr(command[0], '/'))
        return (ft_free_p2(command), NULL);
    else
    {
        cmd = get_path(command[0], env);
        if (strcmp(cmd, command[0]) != 0)
            command[0] = (free(command[0]), cmd);
        return (command);
    }
    return (NULL);
}
