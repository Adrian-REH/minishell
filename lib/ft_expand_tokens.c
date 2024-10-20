/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantill <msantill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:10:57 by adherrer          #+#    #+#             */
/*   Updated: 2024/10/20 18:49:55 by msantill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/headers/minishell.h"

char	*ft_process_quote(char **env, char *line, int code)
{
	char	*result;
	int		i;
	int		flag;
	char	**arr;

	result = ft_strtrim(line, " ");
	flag = ((i = -1), 0);
	arr = NULL;
	while (result[++i])
	{
		if (toggle_quote_flag(&flag, result, i))
		{
			arr = ft_sarraddchr(arr, result[i]);
			continue ;
		}
		if (result[i] == '*' && flag == 0)
		{
			arr = ft_sarradd(arr, resolve_wildcard(&result[i], &i));
			continue ;
		}
		else if (result[i] == '$' && result[i + 1] == '?' && flag != 2)
		{
			arr = ft_sarradd(arr, ft_itoa(code));
			i++;
			continue ;
		}
		else if (result[i] == '$' \
		&& ft_isalpha(result[i + 1]) && flag != 2)
		{
			line = extract_envbyindex(result, result, env, &i);
			arr = ft_sarradd(arr, line);
		}
		else if (result[i] == '\\' && result[i + 1] == 'n' && flag != 2)
			i += (ft_sarradd(arr, "\n"), 1);
		else
			arr = ft_sarraddchr(arr, result[i]);
	}
	if (!arr)
		return (ft_strdup(""));
	return (ft_sarrtostr(arr, ""));
}

void	ft_expand_tokens(t_handler *s)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while (s->info->tokens[++i])
	{
		tmp = s->info->tokens[i];
		if (idstr(s->operators, tmp) == NOT_OPERATOR)
		{
			s->info->tokens[i] = ft_process_quote(s->env, tmp, s->code);
			if (s->info->tokens[i] && tmp)
				free(tmp);
		}
	}
}
