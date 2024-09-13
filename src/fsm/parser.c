#include "../headers/minishell.h"

int evaluate(t_automata *a)
{
	a->ostate = 0;
	a->i = -1;
	while (++a->i < ft_strlen(a->str))
	{
		// printf("---------------------\nlast state: %d |find: %d\n", a->state, idx(a->alphabet, a->str[a->i]));
		a->state = a->get_state(a->state, idx(a->alphabet, a->str[a->i]));
		// printf("new state: %d\n", a->state);
		if (a->fsa[a->state])
		{
			a->fsa[a->state](a, a->data);
		}
		if (a->fta[a->ostate][a->state])
		{
			a->fta[a->ostate][a->state](a, a->data);
		}
		a->ostate = a->state;
	}
	return (a->state);
}

void automata_init(t_automata *a, void *data)
{
	alphabet_init(a);
	errors_init(a);
	sactions_init(a);
	tactions_init(a);
	a->data = data;
	a->get_state = get_state;
}

/**
 * @brief
 *
 * @param s
 *
 * Si tengo la string: cat <"./test_files/file name with spaces" "bye"
 *
 * en el caso de encontrar el ", en token[i] me posiciono.
 * quote_pos:" "bye"
 * token[i - 2] junto con quote_pos: cat "bye"
 * space_pos: name with spaces" "bye"
 * temp: hago una substr tal que len("./test_files/file name with spaces" "bye") - len( name with spaces" "bye")
 * token[i]:./test_files/file
 */
void ft_clean_tokens(t_handler *s)
{
	int i;
	char *space_pos;
	char *quote_pos;
	char *temp;
	char **tokens;
	int state[3];

	tokens = s->info->tokens;
	state[0] = 0;
	state[1] = 0;
	state[2] = 0;
	i = -1;
	while (tokens[++i])
	{
		state[2] = idstr(s->operators, tokens[i]);
		if (state[0] == 14 && (state[1] >= 1 && state[1] < 5) && state[2] == 14 && tokens[i])
		{
			space_pos = ft_strchr(tokens[i], ' ');
			// Reduce the token double quote to the first space, and transfer the rest to the previous token
			if (tokens[i][0] == '\"' && space_pos)
			{
				temp = tokens[i - 2];
				quote_pos = ft_strchr(tokens[i] + 1, '\"');
				if (!quote_pos)
					continue;
				tokens[i - 2] = ft_strjoin(temp, quote_pos + 1);
				free(temp);
				temp = tokens[i];
				temp = ft_substr(temp + 1, 0, ft_strlen(tokens[i]) - ft_strlen(quote_pos) - 1);
				free(tokens[i]);
				tokens[i] = temp;
				continue;
			}
			// Reeplace multiple spaces with a single space, and transfer arguments to the previous token
			if (space_pos)
			{
				temp = tokens[i - 2];
				tokens[i - 2] = ft_strjoin(temp, space_pos);
				free(temp);
				temp = tokens[i];
				tokens[i] = ft_substr(tokens[i], 0, ft_strlen(tokens[i]) - ft_strlen(space_pos));
				free(temp);
			}
		}
		state[0] = state[1];
		state[1] = state[2];
	}
}

t_handler *ft_parser(t_handler *s)
{
	(void)s;
	t_automata a;
	t_data info;
	int finalstate;

	ft_bzero(&a, sizeof(t_automata));
	ft_bzero(&info, sizeof(t_data));
	automata_init(&a, &info);
	a.str = s->line;
	// Inicio la evaluacion de tokens y las dejo en un char **
	finalstate = evaluate(&a);
	if (finalstate > a.errorlen)
		get_token(&a, &info);
	// Podria abrir una funcion para verificas si el ultimo estado puede ser un error de sintaxis
	info.tokens = ft_sarradd(info.tokens, " ");
	info.len_tokens = ft_sarrsize(info.tokens);
	s->info = &info;
	ft_clean_tokens(s);
	// ft_sarrprint(info.tokens);
	return (s);
}

t_handler *ft_clear(t_handler *s)
{

	s->info->tokens = 0;
	s->state[0] = 0;
	s->state[1] = 0;
	s->state[2] = 0;
	s->info = 0;
	return (s);
}
