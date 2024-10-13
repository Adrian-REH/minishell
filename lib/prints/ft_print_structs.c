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

void	ft_print_blocks(t_block *b, int len)
{
	int	i;

	i = 0;
	if (len == 0)
		printf("\t\tNO BLOCK\n");
	while (i < len)
	{
		printf("------------BLOCS %d\n", i);
		printf("\tlen_exec_prev:  %d\n", b->len_exec_prev);
		printf("\tlen_exec_next:  %d\n", b->len_exec_next);
		printf("\tlen_exec:       %d\n", b->len_exec);
		printf("\top:             %d\n", b->op);
		printf("\tpriority:       %d\n", b->priority);
		printf("\ttype:           %d\n", b->type);
		printf("\tfd[0]:          %d | fd[1]: %d\n", b->fd[0], b->fd[1]);
		printf("\tstatus:         %d\n", b->status);
		printf("\tisnext:         %d\n", b->isnext);
		printf("\t------------PREV EXECS\n");
		ft_print_execs(b->prev_exec, b->len_exec_prev);
		printf("\t------------NEXT EXECS\n");
		ft_print_execs(b->next_exec, b->len_exec_next);
		printf("\t------------FILE\n");
		ft_print_file(&(b->file));
		i += ((b += 1), 1);
	}
}

void	ft_print_handler(t_handler *s)
{
	printf("n_pids: %d\n", s->n_pids);
	printf("len_block: %d\n", s->len_block);
	ft_print_blocks(s->block, s->len_block);
	printf("state[0]: %d | state[1]: %d | state[2]: %d \n", \
	s->state[0], s->state[1], s->state[2]);
	printf("code: %d\n", s->code);
}
