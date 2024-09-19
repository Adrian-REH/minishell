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

/**
 * 	Alphabet definitions
 **/
void	alphabet_init(t_automata *a)
{
	a->alphabet = ft_sarradd(NULL, " ");
	a->alphabet = ft_sarradd(a->alphabet, "|");
	a->alphabet = ft_sarradd(a->alphabet, "<");
	a->alphabet = ft_sarradd(a->alphabet, ">");
	a->alphabet = ft_sarradd(a->alphabet, "&");
	a->alphabet = ft_sarradd(a->alphabet, "\"");
	a->alphabet = ft_sarradd(a->alphabet, "\'");
	a->alphabet = ft_sarradd(a->alphabet, "(");
	a->alphabet = ft_sarradd(a->alphabet, ")");
}

/**
 * @brief Get the state object
 * 
 * @param i Estado anterior, valores posibles:
 * 0  Empty input
 * 1  Open double quotes
 * 2  Open single quotes
 * 3  Pipe open
 * 4  Or open
 * 5  Less open
 * 6  Heredoc open
 * 7  Greater open
 * 8  Append open
 * 9  & Found
 * 10 And open
 * 11 Invalid input
 * 12 Spaces without words
 * 13 Spaces between words
 * 14 Not operators
 * 15 Open parenthesis
 * 16 Close parenthesis
 * @param j Estado actual
 * 0 \S
 * 1 |
 * 2 <
 * 3 >
 * 4 &
 * 5 "
 * 6 '
 * 7 (
 * 8 )
 * @return int 
 * 
 * 
 */
int	get_state(int i, int j)
{
	const int	states[][13] = {
	{0, 11, 11, 11, 11, 1, 2, 15, 16, 14, 14, 14},
	{1, 1, 1, 1, 1, 13, 1, 1, 1, 1, 1, 1, 1},
	{2, 2, 2, 2, 2, 2, 13, 2, 2, 2, 2, 2, 2},
	{12, 4, 5, 7, 11, 1, 2, 14, 15, 14, 14, 14, 14},
	{12, 11, 11, 11, 11, 1, 2, 14, 15, 14, 14, 0, 14},
	{12, 11, 6, 11, 11, 1, 2, 14, 15, 14, 14, 14, 14},
	{12, 14, 14, 14, 14, 1, 2, 14, 14, 14, 0, 0, 14},
	{12, 11, 11, 8, 11, 1, 2, 14, 15, 14, 0, 0, 14},
	{12, 11, 11, 11, 11, 1, 2, 14, 15, 14, 0, 0, 14},
	{12, 11, 11, 11, 10, 1, 2, 11, 15, 14, 0, 0, 11},
	{12, 11, 11, 11, 11, 1, 2, 14, 15, 14, 0, 0, 14},
	{11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11},
	{12, 1, 5, 7, 1, 1, 2, 15, 16, 14, 14, 14, 14},
	{13, 3, 5, 7, 9, 1, 2, 15, 16, 14, 14, 14, 14},
	{13, 3, 5, 7, 9, 1, 2, 15, 16, 14, 14, 14, 14},
	{13, 4, 5, 11, 11, 1, 2, 14, 14, 14, 14, 14, 14},
	{13, 4, 5, 11, 11, 1, 2, 14, 14, 14, 14, 14, 14},
	};

	return (states[i][j]);
}

void	errors_init(t_automata *a)
{
	a->errors = NULL;
	a->errors = ft_sarradd(NULL, "Empty string.");
	a->errors = ft_sarradd(a->errors, "Open double quotes");
	a->errors = ft_sarradd(a->errors, "Open single quotes");
	a->errors = ft_sarradd(a->errors, "Pipe open");
	a->errors = ft_sarradd(a->errors, "Or open");
	a->errors = ft_sarradd(a->errors, "Less open");
	a->errors = ft_sarradd(a->errors, "Heredoc open");
	a->errors = ft_sarradd(a->errors, "Greater open");
	a->errors = ft_sarradd(a->errors, "Append open");
	a->errors = ft_sarradd(a->errors, "& Found");
	a->errors = ft_sarradd(a->errors, "And open");
	a->errors = ft_sarradd(a->errors, "Invalid input");
	a->errorlen = ft_sarrsize(a->errors);
}

void	tactions2_init(t_automata *a)
{
	a->fta[AND][NOT_OPERATOR] = (void (*)(void *, void *))get_token;
	a->fta[LESS][SPACES_NW] = (void (*)(void *, void *))get_token;
	a->fta[LESS][NOT_OPERATOR] = (void (*)(void *, void *))get_token;
	a->fta[HEREDOC][SPACES_NW] = (void (*)(void *, void *))get_token;
	a->fta[HEREDOC][NOT_OPERATOR] = (void (*)(void *, void *))get_token;
	a->fta[GREATER][SPACES_NW] = (void (*)(void *, void *))get_token;
	a->fta[GREATER][NOT_OPERATOR] = (void (*)(void *, void *))get_token;
	a->fta[APPEND][SPACES_NW] = (void (*)(void *, void *))get_token;
	a->fta[APPEND][NOT_OPERATOR] = (void (*)(void *, void *))get_token;
	a->fta[OPEN_PAREN][SPACES_BTW] = (void (*)(void *, void *))get_token;
	a->fta[OPEN_PAREN][SPACES_NW] = (void (*)(void *, void *))get_token;
	a->fta[OPEN_PAREN][NOT_OPERATOR] = (void (*)(void *, void *))get_token;
	a->fta[SPACES_BTW][OPEN_PAREN] = (void (*)(void *, void *))get_token;
	a->fta[SPACES_NW][OPEN_PAREN] = (void (*)(void *, void *))get_token;
	a->fta[NOT_OPERATOR][OPEN_PAREN] = (void (*)(void *, void *))get_token;
	a->fta[CLOSE_PAREN][SPACES_BTW] = (void (*)(void *, void *))get_token;
	a->fta[CLOSE_PAREN][SPACES_NW] = (void (*)(void *, void *))get_token;
	a->fta[CLOSE_PAREN][NOT_OPERATOR] = (void (*)(void *, void *))get_token;
	a->fta[SPACES_BTW][CLOSE_PAREN] = (void (*)(void *, void *))get_token;
	a->fta[SPACES_NW][CLOSE_PAREN] = (void (*)(void *, void *))get_token;
	a->fta[NOT_OPERATOR][CLOSE_PAREN] = (void (*)(void *, void *))get_token;
}

void	tactions_init(t_automata *a)
{
	a->fta[NOT_OPERATOR][PIPE] = (void (*)(void *, void *))get_token;
	a->fta[NOT_OPERATOR][LESS] = (void (*)(void *, void *))get_token;
	a->fta[NOT_OPERATOR][GREATER] = (void (*)(void *, void *))get_token;
	a->fta[NOT_OPERATOR][AMPER] = (void (*)(void *, void *))get_token;
	a->fta[SPACES_BTW][PIPE] = (void (*)(void *, void *))get_token;
	a->fta[SPACES_BTW][LESS] = (void (*)(void *, void *))get_token;
	a->fta[SPACES_BTW][GREATER] = (void (*)(void *, void *))get_token;
	a->fta[SPACES_BTW][AMPER] = (void (*)(void *, void *))get_token;
	a->fta[LESS][DQUOTES] = (void (*)(void *, void *))get_token;
	a->fta[GREATER][DQUOTES] = (void (*)(void *, void *))get_token;
	a->fta[HEREDOC][DQUOTES] = (void (*)(void *, void *))get_token;
	a->fta[APPEND][DQUOTES] = (void (*)(void *, void *))get_token;
	a->fta[AMPER][SPACES_NW] = (void (*)(void *, void *))get_token;
	a->fta[AMPER][NOT_OPERATOR] = (void (*)(void *, void *))get_token;
	a->fta[PIPE][SPACES_NW] = (void (*)(void *, void *))get_token;
	a->fta[PIPE][NOT_OPERATOR] = (void (*)(void *, void *))get_token;
	a->fta[OR][SPACES_NW] = (void (*)(void *, void *))get_token;
	a->fta[OR][NOT_OPERATOR] = (void (*)(void *, void *))get_token;
	a->fta[AND][SPACES_NW] = (void (*)(void *, void *))get_token;
	tactions2_init(a);
}
