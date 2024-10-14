/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 23:43:41 by adherrer          #+#    #+#             */
/*   Updated: 2024/07/13 22:21:19 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*dst;

	dst = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!dst)
		return (0);
	i = 0;
	while (s[i])
	{
		dst[i] = f(i, s[i]);
		i++;
	}
	dst[i] = 0;
	return (dst);
}
/* 
static char	ft_(unsigned int	i, char c)
{
	return (i + c);
}
int main()
{
	ft_strmapi("", ft_);
} */