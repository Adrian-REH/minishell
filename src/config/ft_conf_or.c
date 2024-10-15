/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conf_or.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:12:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 08:04:35 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_conf_or(t_handler *s, int i)
{
	(void)i;
	if (s->block[s->info->i].op == 0)
		s->block[s->info->i].op = BLOCK_OR;
	if (s->block[s->info->i].len_exec_next > 0)
	{
		s->info->i++;
		s->block[s->info->i].isnext = 1;
		s->block[s->info->i].len_exec_prev = 0;
		s->block[s->info->i].len_exec_next = 0;
		s->block[s->info->i].next_exec = 0;
		s->block[s->info->i].len_exec = 0;
		s->block[s->info->i].prev_exec = 0;
		s->block[s->info->i].op = BLOCK_OR;
	}
	else if (s->block[s->info->i].len_exec_prev > 0)
		s->block[s->info->i].isnext = 1;
	else
		s->block[s->info->i].isnext = 0;
}
