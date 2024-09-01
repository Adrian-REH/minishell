static int do_exec(char *line, char **env)
{
    char *cmd;
    char **command;

    command = ft_split(line, ' ');
    if (!command)
        (perror("Memory error: "));
    if (*command == 0)
        return (ft_free_p2(command), -1);
    if ((access(command[0], F_OK | X_OK) == 0) && ft_strnstr(command[0], "./", 2))
    {
        if (execve(command[0], command, env) == -1)
            return (ft_free_p2(command), -1);
    }
    else if (access(command[0], F_OK | X_OK) != 0 && ft_strchr(command[0], '/'))
        return (ft_free_p2(command), -1);
    else
    {
        cmd = get_path(command[0], env);
        if (cmd == NULL || execve(cmd, command, env) == -1)
            return (ft_free_p2(command), -1);
        free(cmd);
    }
    return (0);
}