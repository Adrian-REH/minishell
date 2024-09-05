#include "../../headers/minishell.h"

void ft_exec_exit(struct s_cmd *cmd)
{
    printf("%s\n", cmd->cmd[2]);
}