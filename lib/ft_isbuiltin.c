/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isbuiltin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:11:50 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 06:33:22 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/headers/minishell.h"

int	ft_isbuiltin(char **builtins, char *token)
{
	int	i;

	i = -1;
	if (ft_strnstr(token, builtins[0], ft_strlen(token)) \
	&& ft_strnstr(token, "-n", ft_strlen(token)))
		return (1);
	while (builtins[++i])
	{
		if (ft_strnstr(token, builtins[i], ft_strlen(token)))
			return (i);
	}
	return (NOT_OPERATOR);
}
