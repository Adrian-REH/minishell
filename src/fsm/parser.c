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
	// ft_sarrprint(info.tokens);
	info.tokens = ft_sarradd(info.tokens, " ");
	info.len_tokens = ft_sarrsize(info.tokens);
	s->info = &info;

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
