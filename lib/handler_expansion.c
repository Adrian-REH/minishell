/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_concat_fds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:11:16 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/23 01:48:57 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/headers/minishell.h"

int	handle_wildcard(char **arr[], char *result, int *i, int flag)
{
	if (result[*i] == '*' && flag == 0)
	{
		*arr = ft_sarradd(*arr, resolve_wildcard(&result[*i], i));
		return (1);
	}
	return (0);
}

int	handle_exit_code(char **arr[], char *result, int *i, int flag, int code)
{
	if (result[*i] == '$' && result[*i + 1] == '?' && flag != 2)
	{
		*arr = ft_sarradd(*arr, ft_itoa(code));
		(*i)++;
		return (1);
	}
	return (0);
}

int	handle_env_var(char **arr[], char *result, char **env, int *i)
{
	char *line;

	if (result[*i] == '$' && ft_isalpha(result[*i + 1]))
	{
		line = extract_envbyindex(result, result, env, i);
		*arr = ft_sarradd(*arr, line);
		return (1);
	}
	return (0);
}
