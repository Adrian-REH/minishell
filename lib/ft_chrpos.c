/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrpos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:11:19 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 06:28:20 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/headers/minishell.h"

int	ft_chrpos(char *str, int chr, int start)
{
	int	i;
	int	len;

	len = (int)ft_strlen(str);
	if (!str || chr < 0 || start < 0)
		return (-1);
	i = start - 1;
	while (++i < len && str[i])
		if (str[i] == chr)
			return (i);
	return (-1);
}
