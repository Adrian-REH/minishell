/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_idbystr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:11:43 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 06:28:06 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/headers/minishell.h"

int	idstr(char *alphabet[], char *str)
{
	int	i;

	i = -1;
	if (ft_strncmp(str, " ", ft_strlen(str)) == 0)
		return (0);
	while (alphabet[++i])
		if (ft_strncmp(alphabet[i], str, ft_strlen(str)) == 0)
			return (i);
	return (NOT_OPERATOR);
}
