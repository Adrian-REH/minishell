
#include "../headers/minishell.h"

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
