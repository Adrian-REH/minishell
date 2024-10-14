/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:11:29 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 06:32:44 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/headers/minishell.h"

char	*find_str(char *str, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	j = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strncmp(sub, str, ft_strlen(str)) == 0)
			return (free(sub), (env[i] + j + 1));
		i += (free(sub), 1);
	}
	return (NULL);
}
