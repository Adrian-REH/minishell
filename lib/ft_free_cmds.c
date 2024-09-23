/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:12:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/23 01:53:18 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/headers/minishell.h"

void	*ft_free_cmds(t_cmd *cmds, int len)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		if (cmds[i].cmd)
			ft_free_p2(cmds[i].cmd);
		if (cmds[i].line)
			free(cmds[i].line);
		if (is_fd_open(cmds[i].fd_aux[0]))
			close(cmds[i].fd_aux[0]);
		if (is_fd_open(cmds[i].fd_aux[1]))
			close(cmds[i].fd_aux[0]);
	}
	return (NULL);
}
