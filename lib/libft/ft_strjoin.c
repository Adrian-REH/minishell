/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:47:55 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 06:32:22 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;

	dst = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!dst)
		return (0);
	ft_strlcpy(dst, s1, ft_strlen(s2) + ft_strlen(s1) + 1);
	ft_strlcat(dst, s2, ft_strlen(s2) + ft_strlen(s1) + 1);
	return (dst);
}
