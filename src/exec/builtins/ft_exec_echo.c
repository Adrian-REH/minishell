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

char	*extract_and_print_env(char *line, char *result, char **env, int *i)
{
	char	*tmp;

	tmp = NULL;
	tmp = extract_envbyindex(line, result, env, i);
	if (tmp)
		(printf("%s", tmp));
	else
		printf(" ");
	return (tmp);
}

void	ft_process_quote_andprint(struct s_cmd *cmd, char *line)
{
	char	*result;
	int		i;
	int		flag;

	result = ft_strtrim(line, " ");
	flag = ((i = -1), 2);
	while (result[++i])
	{
		if (toggle_flag_printquote(&flag, result, i))
			continue ;
		if (result[i] == '$' && result[i + 1] == '?' && flag)
		{
			(printf("%d", cmd->handler->code), i++);
			continue ;
		}
		else if (result[i] == '$' \
		&& ft_isalpha(result[i + 1]) && flag)
			line = extract_and_print_env(result, result, cmd->handler->env, &i);
		else if (result[i] == '\\' && result[i + 1] == 'n' && flag)
			i += (printf("%c", '\n'), 1);
		else
			printf("%c", result[i]);
	}
}

int	ft_exec_echo(struct s_cmd *cmd)
{
	char	*line;
	int		len;

	line = ft_strnstr(cmd->line, "echo", ft_strlen(cmd->line));
	if (line && (line[4] == ' ' || line[4] == 0))
	{
		len = ft_strlen("echo");
		ft_memmove(line, line + len, strlen(line + len) + 1);
	}
	else
		ft_print_error("command not found ", 2, cmd->line);
	ft_process_quote_andprint(cmd, line);
	printf("\n");
	exit(0);
}

int	ft_exec_echon(struct s_cmd *cmd)
{
	char	*line;
	int		len;

	line = ft_strnstr(cmd->line, "echo", ft_strlen(cmd->line));
	if (line && (line[4] == ' ' || line[4] == 0))
		len = ft_strlen("echo");
	else
		ft_print_error("command not found\n", 127, cmd->line);
	len = 0;
	line = ft_strnstr(cmd->line, "-n", ft_strlen(cmd->line)) + 1;
	while (line[len] == 'n')
		len++;
	if (line[len] != ' ' && line[len] != '\0')
		ft_exec_echo(cmd);
	ft_memmove(line, line + len, strlen(line + len) + 1);
	ft_process_quote_andprint(cmd, line);
	exit(0);
}
