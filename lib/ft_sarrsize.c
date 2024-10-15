/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sarrsize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:12:09 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 06:27:55 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/headers/minishell.h"

int	ft_sarrsize(char **arr)
{
	int	size;

	if (!arr)
		return (0);
	size = 0;
	while (arr[size])
		size++;
	return (size);
}
