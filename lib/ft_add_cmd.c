/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:11:12 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 06:33:32 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/headers/minishell.h"

t_cmd	*add_cmd(t_cmd *cmds, t_cmd cmd)
{
	int	i;

	i = 0;
	if (cmds == NULL)
	{
		cmds = ft_calloc(sizeof(t_cmd), 2);
		cmds[0] = cmd;
		cmds[1].pid = 0;
		return (cmds);
	}
	while (cmds[i].pid)
		i++;
	cmds = ft_realloc(cmds, sizeof(t_cmd) * (i + 2));
	cmds[i++] = cmd;
	return (cmds);
}