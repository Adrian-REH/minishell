#include "../../headers/minishell.h"

size_t ft_strlenchr(char *str, char c)
{
    int i;

    i = 0;
    while (str[i] && str[i] != c)
        i++;
    return i;
}

void ft_process_quote(struct s_cmd *cmd)
{
    char *result;
    int i;
    int j;
    int flag;
    char *line;
    size_t len;
    line = ft_strnstr(cmd->line, "echo", ft_strlen(cmd->line));
    if (line)
    {
        len = ft_strlen("echo"); // Longitud de la subcadena
        memmove(line, line + len, strlen(line + len) + 1);
    }
    // free(line - len);
    result = ft_strtrim(line, " ");
    i = -1;
    flag = 2;
    while (result[++i])
    {
        if (result[i] == '\'')
        {
            if (flag == 1 && ft_strchr(result + i, '\"'))
                printf("\'");
            flag = 0;
            continue;
        }
        if (result[i] == '\"')
        {
            if (!flag && ft_strchr(result + i, '\''))
                printf("\"");
            flag = 1;
            continue;
        }
        if (result[i] == '$' && result[i + 1] == '?' && flag)
        {
            printf("%d", cmd->handler->code);
            i++;
            continue;
        }
        else if (result[i] == '$' && ft_isalpha(result[i + 1]) && flag)
        {
            line = ft_strchr(result + i, ' ') - 1;
            line = ft_substr(result, i + 1, line - result - i);
            line = ft_strtrim(line, "\"");
            j = -1;
            while (cmd->handler->env[++j])
            {
                if (ft_strchr(line, '=') == 0)
                    line = ft_strjoin(line, "=");
                if (!ft_strncmp(cmd->handler->env[j], line, ft_strlen(line)))
                {
                    printf("%s", cmd->handler->env[j] + ft_strlen(line));
                    break;
                }
            }
            i += ft_strlen(line) - 1;
        }
        else
            printf("%c", result[i]);
    }
}
void ft_exec_echo(struct s_cmd *cmd)
{

    ft_process_quote(cmd);
    printf("\n");
    exit(0);
}
void ft_exec_echon(struct s_cmd *cmd)
{

    ft_process_quote(cmd);
    exit(0);
}
