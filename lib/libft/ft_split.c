/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:59:06 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 06:31:44 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_lenword(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		++i;
	}
	return (ft_strlen(s));
}

static int	ft_countword(const char *s, int c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s != c && (s[1] == c || s[1] == 0))
			count++;
		s++;
	}
	return (count);
}

static void	ft_freedom(char **dst)
{
	size_t	n_word;

	n_word = 0;
	while (dst[n_word])
		free(dst[n_word++]);
	free(dst);
}

static char	**ft_(char **dst, const char *s, char c)
{
	size_t	i;
	size_t	size_s;
	size_t	l_word;
	size_t	n_word;

	n_word = 0;
	i = 0;
	size_s = (size_t)ft_strlen(s);
	while (i < size_s && s[i])
	{
		l_word = ft_lenword(s + i, c);
		if (l_word > 0)
		{
			dst[n_word] = ft_substr(s, i, l_word);
			if (!dst[n_word++])
			{
				ft_freedom(dst);
				return ((char **)0);
			}
		}
		i += l_word + 1;
	}
	dst[n_word] = 0;
	return (dst);
}

char	**ft_split(char const *s, char c)
{
	char	**dst;

	if (!s)
		return (0);
	dst = (char **)malloc((ft_countword(s, c) + 1) * sizeof(char *));
	if (!dst)
		return (0);
	dst = ft_(dst, s, c);
	if (!dst)
		return (0);
	return (dst);
}
