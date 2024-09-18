/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:14:16 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 06:21:22 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_exec_pwd(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (cmd->handler->env[++i])
	{
		if (!ft_strncmp(cmd->handler->env[i], "PWD", 3))
			printf("%s\n", cmd->handler->env[i] + 4);
	}
	return (0);
}
