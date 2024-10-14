/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:11:25 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 06:32:34 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/headers/minishell.h"

t_cmd	*delete_cmd(t_cmd *cmds, int i)
{
	int	j;

	j = i;
	ft_free_cmds(&(cmds[i]), 1);
	while (cmds[j].pid)
	{
		cmds[j] = cmds[j + 1];
		j++;
	}
	cmds[j].pid = 0;
	return (cmds);
}
