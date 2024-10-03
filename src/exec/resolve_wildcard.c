/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_wildcard.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:12:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/10/03 18:21:03 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*match_name(char *fname, char *pattern)
{
	char	*start;
	char	*result;

	result = fname;
	while (*pattern)
	{
		if (*pattern == '*')
		{
			if (*(++pattern) == '\0')
				return (result);
			start = strchr(fname, *pattern);
			if (!start)
				return (NULL);
			fname = start;
		}
		else
		{
			if (*fname != *pattern)
				return (NULL);
			fname += (pattern++, 1);
		}
	}
	if (*fname == '\0')
		return (result);
	return (NULL);
}

char	*ft_process_wildcards(char *line, char **arr)
{
	char	*val;
	char	*result;
	int		flag;

	result = ((val = NULL), ft_strdup(""));
	flag = 1;
	while (*arr)
	{
		if (ft_strchr(*arr, '*') && !ft_strchr(*arr, '"' ) \
		&& !ft_strchr(*arr, '\'') && flag)
			val = resolve_wildcard(*arr);
		else if (ft_strchr(*arr, '\'') || ft_strchr(*arr, '\"'))
			flag = !flag;
		if (val)
		{
			result = ((line = result), ft_strjoin(line, val));
			free(line);
			val = ((line = NULL), free(val), NULL);
		}
		else
			result = ft_strjoin(result, *arr);
		if (*(++arr))
		{
			result = ((line = result), ft_strjoin(line, " "));
			if (line)
				free(line);
		}
	}
	return (result);
}

char	*resolve_wildcard(char *str)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*result;
	char			**arr;

	arr = NULL;
	dir = opendir(".");
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_type == DT_REG)
		{
			result = match_name(entry->d_name, str);
			if (result)
				arr = ft_sarradd(arr, result);
		}
		entry = readdir(dir);
	}
	return (ft_sarrtostr(arr));
}
