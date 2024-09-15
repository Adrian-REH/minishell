/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:11:22 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 06:28:19 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/headers/minishell.h"

char	**sarr_clean_quote(char **arr)
{
	int		i;
	char	*line;

	i = -1;
	while (arr[++i])
	{
		line = ft_strtrim(arr[i], "\"");
		free(arr[i]);
		arr[i] = line;
	}
	return (arr);
}
