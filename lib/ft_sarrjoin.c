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

char **ft_sarrjoin(char **arr1, char **arr2)
{
	int i;
	char **result;
	int len1;
	int len2;

	len1 = ft_sarrsize(arr1);
	len2 = ft_sarrsize(arr2);
	result = (char **)malloc((len1 + len2 + 1) * sizeof(char *));
	if (!result) {
		return NULL;
	}
	i = -1;
	while (++i < len1)
		result[i] = ft_strdup(arr1[i]);
	i = -1;
	while (++i < len2) {
		result[len1 + i] = ft_strdup(arr2[i]);
	}
	result[len1 + len2] = NULL;
	ft_free_p2(arr1);
	return result;
}
