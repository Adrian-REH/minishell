#include "../../headers/minishell.h"

char **ft_sarrdel(char **arr, int idx)
{
	char **new;
	int i;
	int j;

	i = -1;
	j = 0;
	new = ft_calloc(sizeof(void *), ft_sarrsize(arr));
	while (arr[++i])
	{
		if (i == idx)
			continue;
		new[j++] = arr[i];
	}
	free(arr);
	return new;
}

void ft_exec_unset(struct s_cmd *cmd)
{
	int i;
	int j;
	char **str;
	char *line;
	size_t len;

	cmd->status = 0;
	line = ft_strnstr(cmd->line, "unset", ft_strlen(cmd->line));
	if (line)
	{
		len = ft_strlen("unset"); // Longitud de la subcadena
		memmove(line, line + len, strlen(line + len) + 1);
	}
	line = ft_strtrim(line, " ");

	str = ft_split(line, ' ');
	i = -1;
	while (cmd->handler->env[++i])
	{
		j = -1;
		while (str[++j])
		{
			if (ft_strncmp(cmd->handler->env[i], str[j], ft_strlen(str[j])) == 0)
			{
				cmd->handler->env = ft_sarrdel(cmd->handler->env, i);
			}
		}
	}
	cmd->status = 0;
}