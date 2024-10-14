/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_learning.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:12:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/20 22:35:04 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	tactions_handler_init2(t_handler *a)
{
	a->fta[NOT_OPERATOR][5][EMPTY] = (void (*)(void *, int))ft_conf_amper;
	a->fta[NOT_OPERATOR][6][EMPTY] = (void (*)(void *, int))ft_conf_pipe;
	a->fta[NOT_OPERATOR][7][EMPTY] = (void (*)(void *, int))ft_conf_or;
	a->fta[NOT_OPERATOR][8][EMPTY] = (void (*)(void *, int))ft_conf_and;
	a->fta[6][1][NOT_OPERATOR] = (void (*)(void *, int))ft_conf_greater;
	a->fta[6][2][NOT_OPERATOR] = (void (*)(void *, int))ft_conf_less;
	a->fta[EMPTY][3][NOT_OPERATOR] = (void (*)(void *, int))ft_conf_heredoc;
}

void	tactions_handler_init(t_handler *a)
{
	a->fta[1][NOT_OPERATOR][0] = (void (*)(void *, int))ft_conf_greater;
	a->fta[2][NOT_OPERATOR][0] = (void (*)(void *, int))ft_conf_less;
	a->fta[4][NOT_OPERATOR][0] = (void (*)(void *, int))ft_conf_append;
	a->fta[EMPTY][UNIQ_COMMAND][EMPTY] = (void (*)(void *, int))ft_conf_cmd;
	a->fta[EMPTY][NOT_OPERATOR][8] = (void (*)(void *, int))ft_conf_cmd;
	a->fta[EMPTY][NOT_OPERATOR][7] = (void (*)(void *, int))ft_conf_cmd;
	a->fta[NOT_OPERATOR][1][NOT_OPERATOR] = \
	(void (*)(void *, int))ft_conf_greater;
	a->fta[NOT_OPERATOR][2][NOT_OPERATOR] = \
	(void (*)(void *, int))ft_conf_less;
	a->fta[NOT_OPERATOR][3][NOT_OPERATOR] = \
	(void (*)(void *, int))ft_conf_heredoc;
	a->fta[NOT_OPERATOR][4][NOT_OPERATOR] = \
	(void (*)(void *, int))ft_conf_append;
	a->fta[NOT_OPERATOR][5][NOT_OPERATOR] = \
	(void (*)(void *, int))ft_conf_amper;
	a->fta[NOT_OPERATOR][6][NOT_OPERATOR] = \
	(void (*)(void *, int))ft_conf_pipe;
	a->fta[NOT_OPERATOR][7][NOT_OPERATOR] = \
	(void (*)(void *, int))ft_conf_or;
	a->fta[NOT_OPERATOR][8][NOT_OPERATOR] = \
	(void (*)(void *, int))ft_conf_and;
	tactions_handler_init2(a);
}

/**
 * 	Operators definitions
 **/
void	operators_init(t_handler *a)
{
	a->operators = ft_sarradd(NULL, " ");
	a->operators = ft_sarradd(a->operators, ">");
	a->operators = ft_sarradd(a->operators, "<");
	a->operators = ft_sarradd(a->operators, "<<");
	a->operators = ft_sarradd(a->operators, ">>");
	a->operators = ft_sarradd(a->operators, "&");
	a->operators = ft_sarradd(a->operators, "|");
	a->operators = ft_sarradd(a->operators, "||");
	a->operators = ft_sarradd(a->operators, "&&");
	a->operators = ft_sarradd(a->operators, "(");
	a->operators = ft_sarradd(a->operators, ")");
	a->operators = ft_sarradd(a->operators, "*");
}

void	errors_init_amper(t_handler *h)
{
	h->ferror[0][OP_HEREDOC][OP_AMPER] = (int (*)(void *, int))syntax_error;
	h->ferror[14][OP_HEREDOC][OP_AMPER] = (int (*)(void *, int))syntax_error;
	h->ferror[0][OP_APPEND][OP_AMPER] = (int (*)(void *, int))syntax_error;
	h->ferror[14][OP_APPEND][OP_AMPER] = (int (*)(void *, int))syntax_error;
	h->ferror[0][OP_PIPE][OP_AMPER] = (int (*)(void *, int))syntax_error;
}

void	tactions_errors_init(t_handler *h)
{
	h->ferror[0][OP_OR][14] = (int (*)(void *, int))syntax_error;
	h->ferror[0][OP_AND][14] = (int (*)(void *, int))syntax_error;
	h->ferror[0][OP_OR][0] = (int (*)(void *, int))syntax_error;
	h->ferror[0][OP_AND][0] = (int (*)(void *, int))syntax_error;
	h->ferror[0][OP_AMPER][0] = (int (*)(void *, int))syntax_error;
	h->ferror[0][OP_GREATER][0] = (int (*)(void *, int))syntax_error;
	h->ferror[0][OP_HEREDOC][0] = (int (*)(void *, int))syntax_error;
	h->ferror[0][OP_APPEND][0] = (int (*)(void *, int))syntax_error;
	h->ferror[0][OP_PIPE][0] = (int (*)(void *, int))syntax_error;
	errors_init_pipe(h);
	errors_init_and(h);
	errors_init_or(h);
	errors_init_heredoc(h);
	errors_init_append(h);
	errors_init_amper(h);
}
