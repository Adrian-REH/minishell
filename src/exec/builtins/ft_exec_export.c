#include "../../headers/minishell.h"

void ft_exec_export(struct s_cmd *cmd)
{
    int i;
    char **str;

    i = -1;
    str = ft_split(cmd->cmd[1], '=');
    while (cmd->handler->env[++i])
    {
        if (ft_strncmp(cmd->handler->env[i], str[0], ft_strlen(str[0])) == 0)
        {
            free(cmd->handler->env[i]);
            cmd->handler->env[i] = cmd->cmd[1];
        }
    }
    if (i == ft_sarrsize(cmd->handler->env))
        cmd->handler->env = ft_sarradd(cmd->handler->env, cmd->cmd[1]);
}