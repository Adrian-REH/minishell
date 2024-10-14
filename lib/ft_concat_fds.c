/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_concat_fds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:11:16 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/23 01:48:57 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/headers/minishell.h"

void	ft_concat_fds(int input, int output)
{
	char	*line;

	line = get_next_line(input);
	while (line)
	{
		ft_putstr_fd(line, output);
		free(line);
		line = get_next_line(input);
	}
}
