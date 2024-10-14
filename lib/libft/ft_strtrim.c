/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 01:14:29 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 06:30:00 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	end;
	size_t	start;

	if (!s1 || !set)
		return (NULL);
	if ((!*s1 && !*set) || (!*s1 && *set))
		return (ft_strdup(""));
	end = ft_strlen(s1);
	start = 0;
	while (ft_strchr(set, s1[end - 1]))
		end--;
	while (ft_strchr(set, s1[start]))
		start++;
	return (ft_substr(s1, start, end - start));
}
