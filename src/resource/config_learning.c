/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_learning.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:12:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 06:24:55 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	tactions_handler_init(t_handler *a)
{
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
	a->fta[NOT_OPERATOR][5][EMPTY] = (void (*)(void *, int))ft_conf_amper;
	a->fta[NOT_OPERATOR][6][EMPTY] = (void (*)(void *, int))ft_conf_pipe;
	a->fta[NOT_OPERATOR][7][EMPTY] = (void (*)(void *, int))ft_conf_or;
	a->fta[NOT_OPERATOR][8][EMPTY] = (void (*)(void *, int))ft_conf_and;
	a->fta[6][1][NOT_OPERATOR] = (void (*)(void *, int))ft_conf_greater;
	a->fta[6][2][NOT_OPERATOR] = (void (*)(void *, int))ft_conf_less;
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
}
