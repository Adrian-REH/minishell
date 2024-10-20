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

char	*add_space(char **arr, char	*result)
{
	char	*tmp;

	tmp = NULL;
	if (*arr)
	{
		result = ((tmp = result), ft_strjoin(tmp, " "));
		if (tmp)
			free(tmp);
	}
	return (result);
}

char	*concat_and_release(char *val, char *result, char **arr)
{
	char	*tmp;

	tmp = result;
	if (val)
	{
		result = ft_strjoin(tmp, val);
		val = (free(tmp), (tmp = NULL), free(val), NULL);
	}
	else
	{
		result = ft_strjoin(tmp, *arr);
		free(tmp);
	}
	if (!result && val)
		return (free(val), NULL);
	return (result);
}

char	*ft_process_wildcards(char **arr)
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
			val = resolve_wildcard(*arr, NULL);
		else if (ft_strchr(*arr, '\'') || ft_strchr(*arr, '\"'))
			flag = !flag;
		result = concat_and_release(val, result, arr);
		result = add_space(++arr, result);
	}
	return (result);
}

char	*resolve_wildcard(char *str, int *j)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*result;
	char			**arr;
	char			**tmp;
	char			*tmpstr;
	int				i;

	arr = NULL;
	tmp = NULL;
	dir = opendir(".");
	entry = readdir(dir);
	i = 0;
	while (str[i] != ' ' && str[i] != '\0' && str[i] != '"'
		&& str[i] != '\'' && str[i] != ' ')
		i++;
	tmpstr = ft_substr(str, 0, i);
	if (!tmpstr)
		return (NULL);
	while (entry)
	{
		if (entry->d_type == DT_REG)
		{
			result = match_name(entry->d_name, tmpstr);
			tmp = arr;
			if (result)
				arr = ft_sarradd(tmp, result);
		}
		entry = readdir(dir);
	}
	free(tmpstr);
	if (j && i)
		*j += i - 1;
	return (ft_sarrtostr(arr, " "));
}
