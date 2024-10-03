/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_greater.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:12:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/22 23:11:56 by adherrer         ###   ########.fr       */
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

	result = ((val = NULL), ft_strdup(""));
	while (*arr)
	{
		if (ft_strchr(*arr, '*') && !ft_strchr(*arr, '"' ) \
		&& !ft_strchr(*arr, '\''))
			val = resolve_wildcard(*arr);
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
