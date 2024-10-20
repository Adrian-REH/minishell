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

int	handle_quote_flag(int *flag, char **arr[], char *result, int i)
{
	if (toggle_quote_flag(flag, result, i))
	{
		*arr = ft_sarraddchr(*arr, result[i]);
		return (1);
	}
	return (0);
}

int	handle_special_sequence(char **arr[], char *result, int *i, int flag)
{
	if (result[*i] == '\\' && result[*i + 1] == 'n' && flag != 2)
	{
		*arr = ft_sarradd(*arr, "\n");
		(*i)++;
		return (1);
	}
	return (0);
}

void	handle_normal_char(char **arr[], char *result, int i)
{
	*arr = ft_sarraddchr(*arr, result[i]);
}

char	*ft_process_quote(char **env, char *result, int code)
{
	char	**arr;
	int		i;
	int		flag;

	flag = ((i = -1), 0);
	arr = NULL;
	while (result[++i])
	{
		if (handle_quote_flag(&flag, &arr, result, i))
			continue ;
		if (handle_wildcard(&arr, result, &i, flag))
			continue ;
		if (handle_exit_code(&arr, result, &i, flag, code))
			continue ;
		if (flag != 2 && handle_env_var(&arr, result, env, &i))
			continue ;
		if (handle_special_sequence(&arr, result, &i, flag))
			continue ;
		handle_normal_char(&arr, result, i);
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
