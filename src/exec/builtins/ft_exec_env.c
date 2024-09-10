#include "../../headers/minishell.h"

void ft_exec_env(struct s_cmd *cmd)
{
    ft_sarrprint(cmd->handler->env);
    cmd->status = 0;
}