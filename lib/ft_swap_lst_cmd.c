/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:11:16 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 06:28:21 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/headers/minishell.h"

void	swap_lst_cmd(t_exec *exec, int i_exec, t_handler *a)
{
	if ((a->state[0] == OP_PIPE || a->state[1] == OP_PIPE) && \
	(a->state[2] >= 1 && a->state[2] <= 4))
	{
		a->info->oid = -1;
		if (exec[i_exec - 1].op)
			exec[i_exec - 1].state[1] = 2;
	}
}
