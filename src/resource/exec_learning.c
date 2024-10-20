/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_learning.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:12:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 06:24:55 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	builtings_init(t_handler *a)
{
	a->builtins = ft_sarradd(a->builtins, "echo");
	a->builtins = ft_sarradd(a->builtins, "echo -n");
	a->builtins = ft_sarradd(a->builtins, "pwd");
	a->builtins = ft_sarradd(a->builtins, "env");
	a->builtins = ft_sarradd(a->builtins, "cd");
	a->builtins = ft_sarradd(a->builtins, "export");
	a->builtins = ft_sarradd(a->builtins, "unset");
	a->builtins = ft_sarradd(a->builtins, "exit");
}

int	st_blk(int sts, int op, int next_op)
{
	int	status[3][2][3];

	if (sts > 0)
		sts = 1;
	status[BLOCK_EMPTY][0][BLOCK_EMPTY] = 0;
	
	status[BLOCK_EMPTY][0][BLOCK_AND] = 0;
	status[BLOCK_EMPTY][1][BLOCK_AND] = 1;
	status[BLOCK_EMPTY][0][BLOCK_OR] = 0;
	status[BLOCK_EMPTY][1][BLOCK_OR] = 1;
	status[BLOCK_OR][0][BLOCK_OR] = 1;
	status[BLOCK_OR][1][BLOCK_OR] = 1;
	status[BLOCK_OR][0][BLOCK_AND] = 0;
	status[BLOCK_OR][1][BLOCK_AND] = 1;
	status[BLOCK_AND][0][BLOCK_AND] = 0;
	status[BLOCK_AND][1][BLOCK_AND] = 1;
	status[BLOCK_AND][0][BLOCK_OR] = 1;
	status[BLOCK_AND][1][BLOCK_OR] = 0;
	status[BLOCK_AND][0][BLOCK_EMPTY] = 0;
	status[BLOCK_AND][1][BLOCK_EMPTY] = 1;
	status[BLOCK_OR][0][BLOCK_EMPTY] = 0;
	status[BLOCK_OR][1][BLOCK_EMPTY] = 1;
	return (status[op][sts][next_op]);
}

void	tactions_builtins_init(t_handler *a)
{
	a->fb[0] = ft_exec_echo;
	a->fb[1] = ft_exec_echon;
	a->fb[2] = ft_exec_pwd;
	a->fb[3] = ft_exec_env;
	a->fb[4] = ft_exec_cd;
	a->fb[5] = ft_exec_export;
	a->fb[6] = ft_exec_unset;
	a->fb[7] = ft_exec_exit;
}
