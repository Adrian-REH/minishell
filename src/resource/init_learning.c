/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_learning.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:34:39 by jvasquez          #+#    #+#             */
/*   Updated: 2024/09/05 12:17:23 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void get_token(t_automata *a, void *data)
{
    char *cmdline;
    char *aux;
    t_data *info;

    info = (t_data *)data;
    cmdline = ft_substr(a->str, a->j, a->i - a->j);
    aux = cmdline;
    cmdline = ft_strtrim(cmdline, " ");
    free(aux);
    a->j = a->i;
    info->tokens = ft_sarradd(info->tokens, cmdline);
    free(cmdline);
}
/**
 * 	Alphabet definitions
 **/
void alphabet_init(t_automata *a)
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
 * 	Operators definitions
 **/
void operators_init(t_handler *a)
{
    // a->operators = ft_sarradd(NULL, " ");
    a->operators = ft_sarradd(a->operators, ">");
    a->operators = ft_sarradd(a->operators, "<");
    a->operators = ft_sarradd(a->operators, "<<");
    a->operators = ft_sarradd(a->operators, ">>");
    a->operators = ft_sarradd(a->operators, "&");
    a->operators = ft_sarradd(a->operators, "|");
    a->operators = ft_sarradd(a->operators, "||");
    a->operators = ft_sarradd(a->operators, "&&");
}

/**
 * 	Builtins definitions
 **/
void builtings_init(t_handler *a)
{
    // a->operators = ft_sarradd(NULL, " ");
    a->builtins = ft_sarradd(a->builtins, "echo");
    a->builtins = ft_sarradd(a->builtins, "echo -n");
    a->builtins = ft_sarradd(a->builtins, "pwd");
    a->builtins = ft_sarradd(a->builtins, "env");
    a->builtins = ft_sarradd(a->builtins, "cd");
    a->builtins = ft_sarradd(a->builtins, "export");
    a->builtins = ft_sarradd(a->builtins, "unset");
    a->builtins = ft_sarradd(a->builtins, "exit");
}

int get_state(int i, int j)
{
    const int states[][13] = {
        //\S,  |,  <,  >,  &,  ",  ', (, )
        {0, 11, 11, 11, 11, 1, 2, 15, 16, NOT_OPERATOR, NOT_OPERATOR, NOT_OPERATOR},                                  // 0  Empty input
        {1, 1, 1, 1, 1, 13, 1, 1, 1, 1, 1, 1, 1},                                                                     // 1  Open double quotes
        {2, 2, 2, 2, 2, 2, 13, 2, 2, 2, 2, 2, 2},                                                                     // 2  Open single quotes
        {12, 4, 5, 11, 11, 1, 2, NOT_OPERATOR, 15, NOT_OPERATOR, NOT_OPERATOR, NOT_OPERATOR, NOT_OPERATOR},           // 3  Pipe open
        {12, 11, 11, 11, 11, 1, 2, NOT_OPERATOR, 15, NOT_OPERATOR, NOT_OPERATOR, 0, NOT_OPERATOR},                    // 4  Or open
        {12, 11, 6, 11, 11, 1, 2, NOT_OPERATOR, 15, NOT_OPERATOR, NOT_OPERATOR, NOT_OPERATOR, NOT_OPERATOR},          // 5  Less open
        {12, 14, 14, 14, 14, 1, 2, NOT_OPERATOR, NOT_OPERATOR, NOT_OPERATOR, 0, 0, NOT_OPERATOR},                     // 6  Heredoc open
        {12, 11, 11, 8, 11, 1, 2, 14, 15, NOT_OPERATOR, 0, 0, NOT_OPERATOR},                                          // 7  Greater open
        {12, 11, 11, 11, 11, 1, 2, 14, 15, NOT_OPERATOR, 0, 0, NOT_OPERATOR},                                         // 8  Append open
        {12, 11, 11, 11, 10, 1, 2, 11, 15, NOT_OPERATOR, 0, 0, 11},                                                   // 9  & Found
        {12, 11, 11, 11, 11, 1, 2, 14, 15, NOT_OPERATOR, 0, 0, NOT_OPERATOR},                                         // 10 And open
        {11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11},                                                         // 11 Invalid input
        {12, 1, 1, 1, 1, 1, 2, 15, 16, NOT_OPERATOR, NOT_OPERATOR, NOT_OPERATOR, NOT_OPERATOR},                       // 12 Spaces without words
        {13, 3, 5, 7, 9, 1, 2, 15, 16, NOT_OPERATOR, NOT_OPERATOR, NOT_OPERATOR, NOT_OPERATOR},                       // 13 Spaces between words
        {13, 3, 5, 7, 9, 1, 2, 15, 16, NOT_OPERATOR, NOT_OPERATOR, NOT_OPERATOR, NOT_OPERATOR},                       // 14 Not operators
        {13, 4, 5, 11, 11, 1, 2, NOT_OPERATOR, NOT_OPERATOR, NOT_OPERATOR, NOT_OPERATOR, NOT_OPERATOR, NOT_OPERATOR}, // 15 Open parenthesis
        {13, 4, 5, 11, 11, 1, 2, NOT_OPERATOR, NOT_OPERATOR, NOT_OPERATOR, NOT_OPERATOR, NOT_OPERATOR, NOT_OPERATOR}, // 16 Close parenthesis
    };

    return (states[i][j]);
}

/**
 * 	Error strings to print when automata finish on a
 * 		non ending state.
 **/
void errors_init(t_automata *a)
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

/**
 *	Simple actions, they trigger when entering a state.
 **/
void sactions_init(t_automata *a)
{
    (void)a;
}

/**
 *	Transition actions, they trigger when going
 * 		from one state to another.
 **/
void tactions_init(t_automata *a)
{
    a->fsa[PIPE] = get_token;
    a->fta[NOT_OPERATOR][PIPE] = get_token;
    a->fta[NOT_OPERATOR][LESS] = get_token;
    a->fta[NOT_OPERATOR][GREATER] = get_token;
    a->fta[NOT_OPERATOR][AMPER] = get_token;
    a->fta[SPACES_BTW][PIPE] = get_token;
    a->fta[SPACES_BTW][LESS] = get_token;
    a->fta[SPACES_BTW][GREATER] = get_token;
    a->fta[SPACES_BTW][AMPER] = get_token;

    a->fta[AMPER][SPACES_NW] = get_token;
    a->fta[AMPER][NOT_OPERATOR] = get_token;
    a->fta[PIPE][SPACES_NW] = get_token;
    a->fta[PIPE][NOT_OPERATOR] = get_token;
    a->fta[OR][SPACES_NW] = get_token;
    a->fta[OR][NOT_OPERATOR] = get_token;
    a->fta[AND][SPACES_NW] = get_token;
    a->fta[AND][NOT_OPERATOR] = get_token;
    a->fta[LESS][SPACES_NW] = get_token;
    a->fta[LESS][NOT_OPERATOR] = get_token;
    a->fta[HEREDOC][SPACES_NW] = get_token;
    a->fta[HEREDOC][NOT_OPERATOR] = get_token;
    a->fta[GREATER][SPACES_NW] = get_token;
    a->fta[GREATER][NOT_OPERATOR] = get_token;
    a->fta[APPEND][SPACES_NW] = get_token;
    a->fta[APPEND][NOT_OPERATOR] = get_token;
    // Parentesis
    a->fta[OPEN_PAREN][SPACES_BTW] = get_token;
    a->fta[OPEN_PAREN][SPACES_NW] = get_token;
    a->fta[OPEN_PAREN][NOT_OPERATOR] = get_token;
    a->fta[SPACES_BTW][OPEN_PAREN] = get_token;
    a->fta[SPACES_NW][OPEN_PAREN] = get_token;
    a->fta[NOT_OPERATOR][OPEN_PAREN] = get_token;

    a->fta[CLOSE_PAREN][SPACES_BTW] = get_token;
    a->fta[CLOSE_PAREN][SPACES_NW] = get_token;
    a->fta[CLOSE_PAREN][NOT_OPERATOR] = get_token;
    a->fta[SPACES_BTW][CLOSE_PAREN] = get_token;
    a->fta[SPACES_NW][CLOSE_PAREN] = get_token;
    a->fta[NOT_OPERATOR][CLOSE_PAREN] = get_token;

    // a->fta[NOT_OPERATOR][CLOSE_PAREN] = get_token;
}

/**
 *	Transision de configuracion,
 *		Se encarga de llamar a la funcion correspondiente, acorde al estado actual.
 **/
void tactions_handler_init(t_handler *a)
{
    a->fta[EMPTY][UNIQ_COMMAND][EMPTY] = ft_conf_cmd;
    a->fta[NOT_OPERATOR][0][NOT_OPERATOR] = ft_conf_greater;
    a->fta[NOT_OPERATOR][1][NOT_OPERATOR] = ft_conf_less;
    a->fta[NOT_OPERATOR][2][NOT_OPERATOR] = ft_conf_heredoc;
    a->fta[NOT_OPERATOR][3][NOT_OPERATOR] = ft_conf_append;
    a->fta[NOT_OPERATOR][4][NOT_OPERATOR] = ft_conf_amper;
    a->fta[NOT_OPERATOR][5][NOT_OPERATOR] = ft_conf_pipe;
    a->fta[NOT_OPERATOR][6][NOT_OPERATOR] = ft_conf_or;
    a->fta[NOT_OPERATOR][7][NOT_OPERATOR] = ft_conf_and;
    a->fta[NOT_OPERATOR][1][EMPTY] = ft_conf_exception;
    a->fta[NOT_OPERATOR][1][EMPTY] = ft_conf_exception;
    a->fta[NOT_OPERATOR][2][EMPTY] = ft_conf_exception;
    a->fta[NOT_OPERATOR][3][EMPTY] = ft_conf_exception;
    a->fta[NOT_OPERATOR][4][EMPTY] = ft_conf_amper;
    a->fta[NOT_OPERATOR][5][EMPTY] = ft_conf_pipe;
    a->fta[NOT_OPERATOR][6][EMPTY] = ft_conf_or;
    a->fta[NOT_OPERATOR][7][EMPTY] = ft_conf_and;
}
/**
 *	Transision de configuracion,
 *		Se encarga de llamar a la funcion correspondiente, acorde al estado actual.
 **/
void tactions_builtins_init(t_handler *a)
{
    a->fb[0] = ft_exec_echo;  // hijo
    a->fb[1] = ft_exec_echon; // hijo
    a->fb[2] = ft_exec_pwd;   // hijo
    a->fb[3] = ft_exec_env;   // hijo
    a->fb[4] = ft_exec_cd;
    a->fb[5] = ft_exec_export;
    a->fb[6] = ft_exec_unset;
    a->fb[7] = ft_exec_exit;
}
