/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:11:22 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 06:28:19 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/headers/minishell.h"

char	*extract_envbyindex(char *line, char *result, t_cmd *cmd, int *i)
{
	char	*tmp;
	int		limit;
	int		j;

	if (ft_strchr(result + *i + 1, '$'))
		line = ft_strchr(result + *i + 1, '$') - 1;
	if (ft_strchr(result + *i + 1, ' '))
		limit = (ft_strchr(result + *i + 1, ' ') - result) - 1;
	else
		limit = ft_strlen(result);
	if (limit - *i > 0)
	{
		tmp = ft_substr(result, *i + 1, limit - *i);
		line = ft_strtrim(tmp, "\"");
		free(tmp);
	}
	if (ft_strchr(line, '=') == 0)
		line = ((tmp = ft_strjoin(line, "=")), free(line), tmp);
	j = -1;
	while (cmd->handler->env[++j])
	{
		if (!ft_strncmp(cmd->handler->env[j], line, ft_strlen(line)))
		{
			*i += ft_strlen(line) - 1;
			return (ft_strdup(cmd->handler->env[j] + ft_strlen(line)));
		}
	}
	return (NULL);
}

char	*extract_env(char *line, char *result, t_cmd *cmd)
{
	char	*tmp;
	int		j;

	if (ft_strchr(result, ' '))
		line = ft_strchr(result, ' ') - 1;
	else if (ft_strchr(result + 1, '$'))
		line = ft_strchr(result + 1, '$') - 1;
	if (line - result > 0)
	{
		tmp = ft_substr(result, 1, line - result);
		line = ft_strtrim(tmp, "\"");
		free(tmp);
	}
	if (ft_strchr(line, '=') == 0)
		line = ((tmp = ft_strjoin(line, "=")), free(line), tmp);
	j = -1;
	while (cmd->handler->env[++j])
	{
		
		if (!ft_strncmp(cmd->handler->env[j], line, ft_strlen(line)))
			return (ft_strdup(cmd->handler->env[j] + ft_strlen(line)));
	}
	return (NULL);
}
