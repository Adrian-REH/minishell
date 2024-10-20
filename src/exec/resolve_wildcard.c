/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_wildcard.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:12:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/10/03 18:29:03 by adherrer         ###   ########.fr       */
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

int	get_substring_length(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '"' && \
	str[i] != '\'' && str[i] != ' ')
		i++;
	return (i);
}

DIR	*open_directory(void)
{
	DIR	*dir;

	dir = opendir(".");
	if (!dir)
		return (NULL);
	return (dir);
}

char	**resolve_matching_files(DIR *dir, char *substr)
{
	struct dirent	*entry;
	char			**arr;
	char			*result;

	arr = NULL;
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_type == DT_REG)
		{
			result = match_name(entry->d_name, substr);
			if (result)
				arr = ft_sarradd(arr, result);
		}
		entry = readdir(dir);
	}
	return (arr);
}

char	*resolve_wildcard(char *str, int *j)
{
	char	**arr;
	char	*substr;
	DIR		*dir;
	int		length;

	arr = NULL;
	dir = open_directory();
	if (!dir)
		return (NULL);
	length = get_substring_length(str);
	substr = ft_substr(str, 0, length);
	if (!substr)
	{
		closedir(dir);
		return (NULL);
	}
	arr = resolve_matching_files(dir, substr);
	free(substr);
	closedir(dir);
	if (j && length)
		*j += length - 1;
	return (ft_sarrtostr(arr, " "));
}
