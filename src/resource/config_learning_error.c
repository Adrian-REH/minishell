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

void	errors_init_pipe(t_handler *h)
{
	h->ferror[OP_LESS][OP_PIPE][0] = (int (*)(void *, int))syntax_error;
	h->ferror[OP_GREATER][OP_PIPE][0] = (int (*)(void *, int))syntax_error;
	h->ferror[OP_APPEND][OP_PIPE][0] = (int (*)(void *, int))syntax_error;
	h->ferror[0][OP_LESS][OP_PIPE] = (int (*)(void *, int))syntax_error;
	h->ferror[0][OP_HEREDOC][OP_PIPE] = (int (*)(void *, int))syntax_error;
	h->ferror[0][OP_APPEND][OP_PIPE] = (int (*)(void *, int))syntax_error;
	h->ferror[0][OP_AND][OP_PIPE] = (int (*)(void *, int))syntax_error;
	h->ferror[0][OP_OR][OP_PIPE] = (int (*)(void *, int))syntax_error;
	h->ferror[14][OP_LESS][OP_PIPE] = (int (*)(void *, int))syntax_error;
	h->ferror[14][OP_HEREDOC][OP_PIPE] = (int (*)(void *, int))syntax_error;
	h->ferror[14][OP_APPEND][OP_PIPE] = (int (*)(void *, int))syntax_error;
	h->ferror[14][OP_AND][OP_PIPE] = (int (*)(void *, int))syntax_error;
	h->ferror[14][OP_OR][OP_PIPE] = (int (*)(void *, int))syntax_error;
}

void	errors_init_and(t_handler *h)
{
	h->ferror[0][OP_GREATER][OP_AND] = (int (*)(void *, int))syntax_error;
	h->ferror[0][OP_LESS][OP_AND] = (int (*)(void *, int))syntax_error;
	h->ferror[0][OP_HEREDOC][OP_AND] = (int (*)(void *, int))syntax_error;
	h->ferror[0][OP_APPEND][OP_AND] = (int (*)(void *, int))syntax_error;
	h->ferror[0][OP_PIPE][OP_AND] = (int (*)(void *, int))syntax_error;
	h->ferror[0][OP_AND][OP_AND] = (int (*)(void *, int))syntax_error;
	h->ferror[0][OP_OR][OP_AND] = (int (*)(void *, int))syntax_error;
	h->ferror[14][OP_GREATER][OP_AND] = (int (*)(void *, int))syntax_error;
	h->ferror[14][OP_LESS][OP_AND] = (int (*)(void *, int))syntax_error;
	h->ferror[14][OP_HEREDOC][OP_AND] = (int (*)(void *, int))syntax_error;
	h->ferror[14][OP_APPEND][OP_AND] = (int (*)(void *, int))syntax_error;
	h->ferror[14][OP_PIPE][OP_AND] = (int (*)(void *, int))syntax_error;
	h->ferror[14][OP_AND][OP_AND] = (int (*)(void *, int))syntax_error;
	h->ferror[14][OP_OR][OP_AND] = (int (*)(void *, int))syntax_error;
}

void	errors_init_or(t_handler *h)
{
	h->ferror[0][OP_GREATER][OP_OR] = (int (*)(void *, int))syntax_error;
	h->ferror[0][OP_LESS][OP_OR] = (int (*)(void *, int))syntax_error;
	h->ferror[0][OP_HEREDOC][OP_OR] = (int (*)(void *, int))syntax_error;
	h->ferror[0][OP_APPEND][OP_OR] = (int (*)(void *, int))syntax_error;
	h->ferror[0][OP_PIPE][OP_OR] = (int (*)(void *, int))syntax_error;
	h->ferror[0][OP_AND][OP_OR] = (int (*)(void *, int))syntax_error;
	h->ferror[0][OP_OR][OP_OR] = (int (*)(void *, int))syntax_error;
	h->ferror[14][OP_GREATER][OP_OR] = (int (*)(void *, int))syntax_error;
	h->ferror[14][OP_LESS][OP_OR] = (int (*)(void *, int))syntax_error;
	h->ferror[14][OP_HEREDOC][OP_OR] = (int (*)(void *, int))syntax_error;
	h->ferror[14][OP_APPEND][OP_OR] = (int (*)(void *, int))syntax_error;
	h->ferror[14][OP_PIPE][OP_OR] = (int (*)(void *, int))syntax_error;
	h->ferror[14][OP_AND][OP_OR] = (int (*)(void *, int))syntax_error;
	h->ferror[14][OP_OR][OP_OR] = (int (*)(void *, int))syntax_error;
}

void	errors_init_heredoc(t_handler *h)
{
	h->ferror[0][OP_LESS][OP_HEREDOC] = (int (*)(void *, int))syntax_error;
	h->ferror[0][OP_GREATER][OP_HEREDOC] = (int (*)(void *, int))syntax_error;
	h->ferror[0][OP_HEREDOC][OP_HEREDOC] = (int (*)(void *, int))syntax_error;
	h->ferror[0][OP_APPEND][OP_HEREDOC] = (int (*)(void *, int))syntax_error;
	h->ferror[0][OP_PIPE][OP_HEREDOC] = (int (*)(void *, int))syntax_error;
	h->ferror[0][OP_AND][OP_HEREDOC] = (int (*)(void *, int))syntax_error;
	h->ferror[0][OP_OR][OP_HEREDOC] = (int (*)(void *, int))syntax_error;
	h->ferror[OP_PIPE][OP_HEREDOC][0] = (int (*)(void *, int))syntax_error;
	h->ferror[OP_AND][OP_HEREDOC][0] = (int (*)(void *, int))syntax_error;
	h->ferror[OP_OR][OP_HEREDOC][0] = (int (*)(void *, int))syntax_error;
	h->ferror[14][OP_LESS][OP_HEREDOC] = (int (*)(void *, int))syntax_error;
	h->ferror[14][OP_GREATER][OP_HEREDOC] = (int (*)(void *, int))syntax_error;
	h->ferror[14][OP_HEREDOC][OP_HEREDOC] = (int (*)(void *, int))syntax_error;
	h->ferror[14][OP_APPEND][OP_HEREDOC] = (int (*)(void *, int))syntax_error;
}

void	errors_init_append(t_handler *h)
{
	h->ferror[0][OP_LESS][OP_APPEND] = (int (*)(void *, int))syntax_error;
	h->ferror[0][OP_GREATER][OP_APPEND] = (int (*)(void *, int))syntax_error;
	h->ferror[0][OP_HEREDOC][OP_APPEND] = (int (*)(void *, int))syntax_error;
	h->ferror[0][OP_APPEND][OP_APPEND] = (int (*)(void *, int))syntax_error;
	h->ferror[0][OP_PIPE][OP_APPEND] = (int (*)(void *, int))syntax_error;
	h->ferror[0][OP_AND][OP_APPEND] = (int (*)(void *, int))syntax_error;
	h->ferror[OP_PIPE][OP_APPEND][0] = (int (*)(void *, int))syntax_error;
	h->ferror[OP_OR][OP_APPEND][0] = (int (*)(void *, int))syntax_error;
	h->ferror[OP_AND][OP_APPEND][0] = (int (*)(void *, int))syntax_error;
	h->ferror[0][OP_OR][OP_APPEND] = (int (*)(void *, int))syntax_error;
	h->ferror[14][OP_LESS][OP_APPEND] = (int (*)(void *, int))syntax_error;
	h->ferror[14][OP_GREATER][OP_APPEND] = (int (*)(void *, int))syntax_error;
	h->ferror[14][OP_HEREDOC][OP_APPEND] = (int (*)(void *, int))syntax_error;
	h->ferror[14][OP_APPEND][OP_APPEND] = (int (*)(void *, int))syntax_error;
}
