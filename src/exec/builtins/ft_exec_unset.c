#include "../../headers/minishell.h"

void ft_exec_unset(struct s_cmd *cmd)
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
			cmd->handler->env[i] = 0;
			// cmd->handler->env[i] = cmd->cmd[1];
		}
	}
}