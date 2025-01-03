/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:11:53 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 06:33:47 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/headers/minishell.h"

void	*ft_realloc(void *ptr, size_t size_old, size_t size)
{
	void	*new;

	new = malloc(size);
	if (!new)
		return (NULL);
	if (ptr)
	{
		ft_memcpy(new, ptr, size_old);
		free(ptr);
	}
	if (size > size_old)
		ft_bzero(new + size_old, size - size_old);
	return (new);
}
