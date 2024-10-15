/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 16:43:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/08/02 19:03:48 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n <= 0)
		return (-1);
	while (n-- > 0)
	{
		if (*s1 != *s2++)
			return (*(unsigned char *)(s1) - *(unsigned char *)(s2 - 1));
		if (!(*s1++))
			return (0);
	}
	return (0);
}
/* int	main()
{
	char	s1[] = "elias";
	char	s2[] = "adrian";

	ft_strncmp(s1,s2, 6);
} */