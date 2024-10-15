/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 00:19:22 by adherrer          #+#    #+#             */
/*   Updated: 2024/07/27 16:55:12 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	char	*str;

	str = ft_strjoin(s, "\n");
	ft_putstr_fd(str, fd);
	free(str);
}
/* int	main()
{
	char s[] = "adrian";
	ft_putendl_fd(s, 1);
} */