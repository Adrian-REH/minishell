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

#include "../src/headers/minishell.h"

void ft_print_file(t_file *f)
{
	printf("\t\tinput:        %d\n", f->input);
	printf("\t\toutput:       %d\n", f->output);
	printf("\t\tfd_aux[0]:    %d | fd_aux[1]: %d\n", f->fd_aux[0], f->fd_aux[1]);
	printf("\t\tlen_content:  %d\n", f->len_content);
	printf("\t\tidfile:       %s\n", f->idfile);
	printf("\t\todfile:       %s\n", f->odfile);
	printf("\t\tend_heredoc:  %s\n", f->end_heredoc);
}

void ft_print_cmds(t_cmd *c)
{
	int i = 2;
	int j = 0;
	while (j < i)
	{
		//ft_sarrprint(c->cmd);
		printf("\t\t------------CMD %d\n", j);
		printf("\t\tline:         %s\n", c->line);
		printf("\t\tfd_aux[0]:    %d | fd_aux[1]: %d\n", c->fd_aux[0], c->fd_aux[1]);
		printf("\t\tpid:          %d\n", c->pid);
		printf("\t\tstatus:       %d\n", c->status);
		printf("\t\ttowait:       %d\n", c->towait);
		c++;
		j++;
	}
}

void ft_print_execs(t_exec *e, int len)
{
	int i = 0;
	if (len == 0)
		printf("\t\t(NO EXEC)\n");
	while (i < len)
	{
		printf("\t------------EXEC %d\n", i);
		printf("\tpriority:     %d\n", e->priority);
		printf("\tfinish:       %d\n", e->finish);
		printf("\tstate[0]:     %d | state[1]: %d | state[2]: %d\n", e->state[0], e->state[1], e->state[2]);
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

void ft_print_blocks(t_block *b, int len)
{
	int i = 0;
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
		ft_print_execs(b->next_exec,  b->len_exec_next);
		printf("\t------------FILE\n");
		ft_print_file(&(b->file));
		b++;
		i++;
	}
}


void ft_print_handler(t_handler *s)
{
	printf("n_pids: %d\n", s->n_pids);
	printf("len_block: %d\n", s->len_block);
	ft_print_blocks(s->block,  s->len_block);
	//printf("-------------------CMDS\n");
	//ft_print_cmds(s->w_cmd);
	printf("n_pids: %d\n", s->n_pids);
	printf("state[0]: %d | state[1]: %d | state[2]: %d \n", s->state[0], s->state[1], s->state[2]);
	printf("code: %d\n", s->code);
}