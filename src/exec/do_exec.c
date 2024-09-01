
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
    {
        return (command);
        // Tengo que retornarla la matriz de comandos, ya que si tengo acceso
        /*
        if (execve(command[0], command, env) == -1)
            return (ft_free_p2(command), -1);
    */
    }
    else if (access(command[0], F_OK | X_OK) != 0 && ft_strchr(command[0], '/'))
        return (ft_free_p2(command), -1);
    else
    {
        cmd = get_path(command[0], env);
        free(command[0]);
        command[0] = cmd;
        return (command);
        /*
        if (cmd == NULL || execve(cmd, command, env) == -1)
            return (ft_free_p2(command), -1);
        */
    }

    return (NULL);
}
static int do_access(char *dir)
{

    access(dir, F_OK | X_OK);        // Para saber si el directorio existe
    access("text.txt", R_OK | W_OK); // para saber si se puede leer y escribir en el archivo
    return (0);
}