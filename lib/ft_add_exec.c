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

t_exec	*add_exec(t_exec *execs, t_exec exec)
{
	int	i;

	i = 0;
	if (execs == NULL)
	{
		printf("calloc\n");
		execs = ft_calloc(sizeof(t_exec), 2);
		execs[0] = exec;
		execs[1].op = 0;
		return (execs);
	}
	while (execs[i].op)
		i++;
	printf("realloc: %d\n", i);
	execs = ft_realloc(execs, sizeof(t_exec) * i, sizeof(t_exec) * (i + 2));
	execs[i++] = exec;
	execs[i] = (t_exec){0};
	return (execs);
}
