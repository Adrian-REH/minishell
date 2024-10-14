/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_execs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:12:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/23 01:53:16 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/headers/minishell.h"

void	*ft_free_execs(t_exec *execs, int len)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		if (execs[i].cmd)
		{
			ft_free_cmds(execs[i].cmd, 2);
			free(execs[i].cmd);
			execs[i].cmd = NULL;
		}
		if (execs[i].file.end_heredoc)
			free(execs[i].file.end_heredoc);
		if (execs[i].state)
			free(execs[i].state);
	}
	return (NULL);
}
