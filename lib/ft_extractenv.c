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

char	*get_env_substr(char**env, char *line, int *i, int j)
{
	while (env[++j])
	{
		if (!ft_strncmp(env[j], line, ft_strlen(line)))
		{
			*i += ft_strlen(line) - 1;
			return (ft_strdup(env[j] + ft_strlen(line)));
		}
	}
	return (NULL);
}

int	ft_ischrenv(char c)
{
	return ((ft_isalnum(c) || c == '_') && c != ' ' && c != '$');
}

char	*extract_envbyindex(char *line, char *result, char **env, int *i)
{
	char	*tmp;
	int		limit;
	int		j;

	limit = 0;
	while (ft_ischrenv(result[*i + limit + 1]))
		limit++;
	if (limit > 0)
	{
		tmp = ft_substr(result, *i + 1, limit);
		line = ft_strtrim(tmp, "\"");
		free(tmp);
	}
	if (ft_strchr(line, '=') == 0)
		line = ((tmp = ft_strjoin(line, "=")), free(line), tmp);
	j = -1;
	tmp = get_env_substr(env, line, i, j);
	if (!tmp)
		return ((*i += ft_strlen(line) - 1), NULL);
	return (tmp);
}

char	*extract_env(char *line, char *result, char **env)
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
	while (env[++j])
	{
		if (!ft_strncmp(env[j], line, ft_strlen(line)))
			return (ft_strdup(env[j] + ft_strlen(line)));
	}
	return (NULL);
}
