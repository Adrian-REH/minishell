/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_structs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:10:57 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/23 01:31:46 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/headers/minishell.h"

void	ft_print_cmds(t_cmd *c)
{
	int	i;
	int	j;

	i = 2;
	j = 0;
	while (j < i)
	{
		printf("\t\t------------CMD %d\n", j);
		printf("\t\tcmd dir:      %p\n", c->cmd);
		printf("\t\tline:         %s\n", c->line);
		printf("\t\tfd_aux[0]:    %d | fd_aux[1]: %d\n", \
		c->fd_aux[0], c->fd_aux[1]);
		printf("\t\tpid:          %d\n", c->pid);
		printf("\t\tstatus:       %d\n", c->status);
		printf("\t\ttowait:       %d\n", c->towait);
		c++;
		j++;
	}
}
