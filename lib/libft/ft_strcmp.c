/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 16:43:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/07/20 14:53:47 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
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