#include "../../headers/minishell.h"

char *ft_deletechar(char *str, char c)
{
    int i;
    int j;
    char *result;

    i = -1;
    j = 0;
    result = malloc(sizeof(char) * (ft_strlen(str) + 1));
    while (str[++i])
    {
        if (str[i] == c)
            continue;
        result[j++] = str[i];
    }
    str[i] = 0;
    result[j] = 0;
    // result = ft_realloc(result, ft_strlen(result) + 1);
    return result;
}

void ft_exec_echo(struct s_cmd *cmd)
{
    char *result;
    int i;

    i = 0;
    while (cmd->cmd[++i])
    {
        result = ft_deletechar(cmd->cmd[i], '\"');
        result = ft_deletechar(result, '\'');
        if (ft_strnstr(result, "$?", ft_strlen(result)))
            printf("%d", cmd->handler->code);
        else
            printf("%s", result);
        free(result);
        if (cmd->cmd[i + 1])
            printf(" ");
    }
    printf("\n");
    exit(0);
}

void ft_exec_echon(struct s_cmd *cmd)
{
    char *result;
    int i;

    i = 0;
    while (cmd->cmd[++i])
    {
        result = ft_strtrim(cmd->cmd[i], "\"");
        result = ft_strtrim(result, "\'");
        if (ft_strnstr(result, "$?", ft_strlen(result)))
            printf("%d", cmd->handler->code);
        else
            printf("%s", result);
        free(result);
        if (cmd->cmd[i + 1])
            printf(" ");
    }
    exit(0);
}
