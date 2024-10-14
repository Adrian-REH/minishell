/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_blocks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:12:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/23 01:53:20 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/headers/minishell.h"

void	*ft_free_blocks(t_block *block, int len)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		ft_free_execs(block[i].prev_exec, block[i].len_exec_prev);
		free(block[i].prev_exec);
		ft_free_execs(block[i].next_exec, block[i].len_exec_next);
		free(block[i].next_exec);
		if (is_fd_open(block[i].fd[0]) && block[i].fd[0] != 0)
			close(block[i].fd[0]);
		if (is_fd_open(block[i].fd[1]) && block[i].fd[1] != 1)
			close(block[i].fd[0]);
		ft_free_file(&block[i].file);
	}
	return (NULL);
}
