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

void *ft_free_info(t_data *info)
{
	ft_free_p2(info->tokens);
	return (NULL);
}

t_handler	*ft_clear(t_handler *s)
{
	s->len_block = 0;
	ft_free_blocks(s->block, s->len_block);
	free(s->block);
	s->block = NULL;
	s->info = NULL;
	//ft_free_info(s->info);
	//s->info = NULL;
	s->state[0] = 0;
	s->state[1] = 0;
	s->state[2] = 0;
	return (s);
}
