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

void	ft_print_execs(t_exec *e, int len)
{
	int	i;

	i = 0;
	if (len == 0)
		printf("\t\t(NO EXEC)\n");
	while (i < len)
	{
		printf("\t------------EXEC %d\n", i);
		printf("\tpriority:     %d\n", e->priority);
		printf("\tfinish:       %d\n", e->finish);
		printf("\tstate_dir:       %p\n", e->state);
		printf("\tstate[0]:     %d | state[1]: %d | state[2]: %d\n", \
		e->state[0], e->state[1], e->state[2]);
		printf("\top:           %d\n", e->op);
		printf("\tstatus:       %d\n", e->status);
		printf("\t------------FILE\n");
		ft_print_file(&(e->file));
		printf("\t------------CMD\n");
		ft_print_cmds(e->cmd);
		e++;
		i++;
	}
}
