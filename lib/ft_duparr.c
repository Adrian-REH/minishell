/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_duparr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:10:57 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 06:34:25 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/headers/minishell.h"

char	**duparr(char **argenv)
{
	char	**arr;
	int		i;

	i = -1;
	if (!argenv || !*argenv)
		return (NULL);
	arr = malloc(sizeof(char *) * (ft_sarrsize(argenv) + 1));
	while (argenv[++i])
		arr[i] = ft_strdup(argenv[i]);
	arr[i] = NULL;
	return (arr);
}
