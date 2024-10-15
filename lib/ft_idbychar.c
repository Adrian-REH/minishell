/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_idbychar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:11:39 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 06:28:10 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/headers/minishell.h"

int	idx(char *alphabet[], char c)
{
	int	i;

	i = -1;

	if (ft_chrpos("\t\n\v\f\r ", c, 0) != -1)
		return (0);
	while (alphabet[++i])
		if (ft_chrpos(alphabet[i], c, 0) != -1)
			return (i);
	return (i);
}
