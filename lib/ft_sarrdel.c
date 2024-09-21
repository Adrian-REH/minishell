/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sarrdel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:59:20 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/20 23:26:28 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/headers/minishell.h"

char	**ft_sarrdel(char **arr, char *string)
{
	int		size;
	int		j;

	if (!string)
		return (arr);
	while (arr[size])
	{
		if (ft_strcmp(arr[size], string))
		{
			j = size;
			while (arr[j])
			{
				arr[j] = arr[j + 1];
				j++;
			}
		}
		else
			size++;
	}
	return (arr);
}

char	**ft_sarrdelbyindex(char **arr, int idx)
{
	char	**new;
	int		i;
	int		j;

	i = -1;
	j = 0;
	new = ft_calloc(sizeof(void *), ft_sarrsize(arr) + 1);
	while (arr[++i])
	{
		if (i == idx)
			continue ;
		new[j++] = arr[i];
	}
	new[j] = NULL;
	return (new);
}