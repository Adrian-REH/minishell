#include "../../headers/minishell.h"
void ft_exec_echo(struct s_cmd *cmd)
{
    char *result;

    result = ft_strtrim(cmd->cmd[1], "\"");
    if (ft_strnstr(result, "$?", ft_strlen(result)))
        printf("%d\n", cmd->handler->code);
    else
        printf("%s\n", result);
    free(result);
    exit(0);
}

void ft_exec_echon(struct s_cmd *cmd)
{
    char *result;

    result = ft_strtrim(cmd->cmd[2], "\"");
    if (ft_strnstr(result, "$?", ft_strlen(result)))
        printf("%d", cmd->handler->code);
    else
        printf("%s", result);
    exit(0);
}
