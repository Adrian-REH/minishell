#include "../../headers/minishell.h"

static void	change_env(t_cmd *cmd)
{
	int		i;
	char	*temp;
    char *s;

	i = -1;
    str  = ft_split(cmd->cmd[1], '=');
	while (cmd->handler->env[++i])
	{
		if (ft_strncmp(cmd->handler->env[i], str[0], ft_strlen(str[0])) == 0)
		{
            free(cmd->handler->env[i]);
            cmd->handler->env[i] = cmd->cmd[1];
		}
        else
            cmd->handler->env = ft_sarradd(cmd->handler->env, cmd->cmd[1]);
	}
}
void ft_exec_unset(struct s_cmd *cmd)
{
    change_env(cmd);
}