/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:14:01 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 06:21:11 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

size_t	ft_strlenchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

void	ft_process_quote(struct s_cmd *cmd, char *line)
{
	char	*result;
	int		i;
	int		j;
	int		flag;

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
			continue ;
		}
		if (result[i] == '\"')
		{
			if (!flag && ft_strchr(result + i, '\''))
				printf("\"");
			flag = 1;
			continue ;
		}
		if (result[i] == '$' && result[i + 1] == '?' && flag)
		{
			printf("%d", cmd->handler->code);
			i++;
			continue ;
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
					break ;
				}
			}
			i += ft_strlen(line) - 1;
		}
		else
			printf("%c", result[i]);
	}
}

int	ft_exec_echo(struct s_cmd *cmd)
{
	char	*line;
	int		len;

	line = ft_strnstr(cmd->line, "echo", ft_strlen(cmd->line));
	if (line)
	{
		len = ft_strlen("echo");
		memmove(line, line + len, strlen(line + len) + 1);
	}
	ft_process_quote(cmd, line);
	printf("\n");
	exit(0);
}

int	ft_exec_echon(struct s_cmd *cmd)
{
	char	*line;
	int		len;


	line = ft_strnstr(cmd->line, "echo", ft_strlen(cmd->line));
	if (line)
	{
		len = ft_strlen("echo");
		memmove(line, line + len, strlen(line + len) + 1);
	}
	len = 0;
	line = ft_strnstr(cmd->line, "-n", ft_strlen(cmd->line)) + 1;
	while (line[len] == 'n')
		len++;
	memmove(line, line + len, strlen(line + len) + 1);
	ft_process_quote(cmd, line);
	exit(0);
}
