#include "../../headers/minishell.h"

void ft_exec_export(struct s_cmd *cmd)
{
    printf("%s\n", cmd->cmd[2]);
}