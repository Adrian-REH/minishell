/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:16:40 by adherrer          #+#    #+#             */
/*   Updated: 2024/07/13 22:21:19 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countdigit(int n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n > 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static char	*ft_str(int l_digit)
{
	char	*src;

	src = malloc((l_digit + 1) * sizeof(char));
	if (!src)
		return (0);
	src[l_digit] = 0;
	return (src);
}

char	*ft_itoa(int n)
{
	int		l_digit;
	char	*src;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	l_digit = ft_countdigit(n);
	src = ft_str(l_digit--);
	if (!src)
		return (0);
	if (n < 0)
	{
		src[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		*(src + l_digit--) = (n % 10) + '0';
		n /= 10;
	}
	return (src);
}

/* 

int main()
{
	char	*p2 = ft_itoa(-2147483647 -1); 
	char	*p = ft_itoa(8124); 
	char	*p1 = ft_itoa(-10); 
	char	*p3 = ft_itoa(0); 
}  */