#include "../../headers/minishell.h"
void ft_exec_pwd(t_cmd *cmd)
{
    int i;

    i = -1;
    while (cmd->handler->env[++i])
    {
        if (!ft_strncmp(cmd->handler->env[i], "PWD", 3))
            printf("%s\n", cmd->handler->env[i] + 4);
    }
}