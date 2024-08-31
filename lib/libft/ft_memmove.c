/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 23:12:29 by adherrer          #+#    #+#             */
/*   Updated: 2024/07/13 22:21:19 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*val;
	char	*var;

	if (!dst && !src)
		return (dst);
	var = (char *)dst;
	val = (char *)src;
	if (var > val)
		while (len-- > 0)
			*(var + len) = *(val + len);
	else
		while (len-- > 0)
			*var++ = *val++;
	return (dst);
}
/* int	main()
{
	char	s1[] = "adrian";
	char	s2[] = "adrian ramon elias";
	ft_memmove(s1, s2, 19);
} */