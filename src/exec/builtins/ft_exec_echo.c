#include "../../headers/minishell.h"


size_t ft_strlenchr(char *str, char c)
{
    int i;

    i = 0;
    while (str[i] && str[i] != c)
        i++;
    return i;
}
char *ft_del_q(char *str, char c)
{
    char *start;
    char *end;
    char *result;
    char **arr;
    arr = 0;
    while(1)
    {
        if (ft_strchr(str, c) == 0)
        {
            arr = ft_sarradd(arr, str);
            break;
        }
        start = ft_strchr(str, c);
        end = ft_strrchr(str , c);
        if ((!start || !end) || (start == end))
        {
            return str;
        }
        start++;
        if (start)
        {
            result = ft_substr(str, 0, start - str - 1);
            arr = ft_sarradd(arr, result);
        }
        if (end)
        {
            result = ft_substr(str, end - str + 1, end - str);
            arr = ft_sarradd(arr, result);
        }
        str = ft_substr(str, start - str, end - start);
    }
    result = "";
    int i;
    i = -1;
    if (!arr)
        result = str;
    while (arr[++i])
    {
       // if (ft_sarrsize(arr) == i / 2)
        //    result = ft_strjoin(result, str);
        result = ft_strjoin(result, arr[i]);
    }
    return result;
}
void ft_process_quote(struct s_cmd *cmd)
{
    char *result;
    char *line;
    size_t len;
    int state[2];
    int i;
    int j;
    int flag;
    state[0] = 0;
    state[1] = 0;
    line = ft_strnstr(cmd->line, "echo", ft_strlen(cmd->line));
    if (line) {
        len = ft_strlen("echo"); // Longitud de la subcadena
        memmove(line, line + len, strlen(line + len) + 1);
    }
    //free(line - len);
    result = ft_strtrim(line, " ");
    i = -1;
    flag = 0;
    while (result[++i])
    {
        if (result[i] == '\'')
        {
            state[0] = state[1];
            state[1] = 1;
            if (!state[0])
                flag = 0;
            continue;
        }
        if (result[i] == '\"')
        {
            state[0] = state[1];
            state[1] = 2;
            if (!state[0])
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
    printf("\n");

}
void ft_exec_echo(struct s_cmd *cmd)
{
    char *result;
    char *line;
    size_t len;
    int i;
    int j;
    (void)i;
    (void)j;
//ft_process_quote(cmd);
//return ;
    line = ft_strnstr(cmd->line, "echo", ft_strlen(cmd->line));
    if (line) {
        len = ft_strlen("echo"); // Longitud de la subcadena
        //memmove(line, line + len, strlen(line + len) + 1);
        printf("val: %ld\n", ft_strlen(line) - len);
        line = ft_substr(line, len, ft_strlen(line) - len);
    }
    //line = ft_strtrim(line, " ");
    //result = ft_del_q(line, '\"');
    //result = ft_del_q(result, '\'');
    i = -1;
    result = line;
    printf("%s\n", result);
     while (result[++i])
    {
        if (result[i] == '$' && result[i + 1] == '?')
        {
            printf("%d", cmd->handler->code);
            i++;
            continue;
        }
        else if (result[i] == '$' && ft_isalpha(result[i + 1]))
        {
            line = ft_strchr(result + i, ' ') - 1;
            line = ft_substr(result, i + 1, line - result - i);
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
    //NO difiere entre '' y "" para procesar los $, aparte no imprime el ultimo caracter
    printf("\n");
    exit(0);
}

void ft_exec_echon(struct s_cmd *cmd)
{
    char *result;
    char *line;
    int     i;
    int j;
    size_t len;

    line = ft_strnstr(cmd->line, "echo", ft_strlen(cmd->line));
    if (line) {
        len = ft_strlen("echo"); // Longitud de la subcadena
        memmove(line, line + len, strlen(line + len) + 1);
    }
    line = ft_strtrim(line, " ");
    result = ft_del_q(line, '\"');
    result = ft_del_q(result, '\'');

    i = -1;
    if (ft_strnstr(result, "$", ft_strlen(result)))
    {
        while (result[++i])
        {
            if (result[i] == '$')
            {
                line = ft_strchr(result + i, ' ');
                line = ft_substr(result, i + 1, line - result + i);
                j = -1;
                while (cmd->handler->env[++j])
                {
                    if (!ft_strncmp(cmd->handler->env[j], line, ft_strlenchr(line, '=')))
                        printf("%s\n", cmd->handler->env[j] + ft_strlenchr(line, '=') + 1);
                }
            }
        }
    }
    else if (ft_strnstr(result, "$?", ft_strlen(result)))
        printf("%d", cmd->handler->code);
    else
        printf("%s", result);
    free(result);

    exit(0);
}
