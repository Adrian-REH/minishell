/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:12:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/24 18:04:59 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_handler	*ft_clear(t_handler *s)
{
	if (s->block)
		(ft_free_blocks(s->block, s->len_block), free(s->block));
	s->len_block = 0;
	if (s->info)
	{
		ft_free_p2(s->info->tokens);
		free(s->info);
		s->info = NULL;
	}
	if (s->a)
	{
		ft_free_p2(s->a->alphabet);
		s->a->alphabet = NULL;
		ft_free_p2(s->a->errors);
		s->a->errors = NULL;
		free(s->a->str);
		free(s->a);
		s->a = NULL;
	}
	s->info = NULL;
	s->block = NULL;
	s->state[0] = 0;
	s->state[1] = 0;
	s->state[2] = 0;
	return (s);
}
