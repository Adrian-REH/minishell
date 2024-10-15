/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sarradd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:11:56 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 06:28:00 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/headers/minishell.h"

char	**ft_sarradd(char **arr, char *string)
{
	int		size;
	char	**new_arr;

	if (!string)
		return (arr);
	size = ft_sarrsize(arr) + 2;
	new_arr = malloc(sizeof(char *) * (size));
	size = 0;
	if (arr)
	{
		while (arr[size])
		{
			new_arr[size] = ft_strdup(arr[size]);
			size++;
		}
		ft_sarrfree(&arr);
	}
	new_arr[size++] = ft_strdup(string);
	new_arr[size] = NULL;
	return (new_arr);
}

char	**ft_sarraddchr(char **arr, char string)
{
	int		size;
	char	**new_arr;

	if (!string)
		return (arr);
	size = ft_sarrsize(arr) + 2;
	new_arr = malloc(sizeof(char *) * (size));
	size = 0;
	if (arr)
	{
		while (arr[size])
		{
			new_arr[size] = ft_strdup(arr[size]);
			size++;
		}
		ft_sarrfree(&arr);
	}
	new_arr[size++] = ft_strdup(&string);
	new_arr[size] = NULL;
	return (new_arr);
}

char	**ft_sarraddbyindex(char **arr, char *string, int i)
{
	int		size;
	int		j;
	char	**new_arr;

	if (!string)
		return (arr);
	size = ft_sarrsize(arr) + 2;
	new_arr = malloc(sizeof(char *) * (size));
	size = 0;
	j = 0;
	if (arr)
	{
		while (arr[size])
		{
			if (size == i)
				new_arr[j++] = ft_strdup(string);
			new_arr[j] = ft_strdup(arr[size]);
			size++;
			j++;
		}
		ft_sarrfree(&arr);
	}
	return ((new_arr[j] = NULL), new_arr);
}
