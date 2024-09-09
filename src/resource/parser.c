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

int *handler_execute(t_handler *a)
{
	int i = -1;
	int j = 0;

	// a->exec[0].file.input = 0;
	while (a->info->tokens[++i])
	{

		a->state[2] = idstr(a->operators, a->info->tokens[i]);
		a->exec[a->info->i].handler = a;
		if (strcmp("(", a->info->tokens[i]) == 0)
			a->exec[a->info->i].priority = 1;
		else if (strcmp(")", a->info->tokens[i]) == 0)
			a->exec[a->info->i].priority = 0;
		if (a->exec[a->info->i].priority)
			a->exec[a->info->i].priority = 1;
		// Verifico si es un cmd o un file o si es un idstr
		if (a->state[1] == NOT_OPERATOR)
		{
			if (do_exec(a->info->tokens[i - 1], a->env) && a->state[2] == EMPTY)
				a->state[1] = UNIQ_COMMAND;
		}
		if (a->state[0] == 5 && a->state[2] == 2)
		{
			a->info->oid = -1;
			a->exec[a->info->i - 1].state[1] = 2;
		}
		// printf("state[0]: %d | state[1]: %d | state[2]: %d\n", a->state[0], a->state[1], a->state[2]);
		// VErifico si el cmd es un built-in y que tipo es
		if (a->fta[a->state[0]][a->state[1]][a->state[2]])
		{
			j++;
			a->fta[a->state[0]][a->state[1]][a->state[2]](a, i - 1);
		}
		a->len_exec = j;
		a->state[0] = a->state[1];
		a->state[1] = a->state[2];
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
void init_handler(t_handler *s)
{
	operators_init(s);
	builtings_init(s);
	tactions_handler_init(s);
	tactions_builtins_init(s);
	s->code = 0;
}

/**
 * @brief
 *
 * @param s
 * @return * int*
 * Debo ejecutar todos los comandos y sus funciones
 * todos los comandos ejecutaran sus respectivas funciones y devolvera el estado actual y el anterior, para
 * poder ejecutar la siguiente funcion. El objetivo es poder ejecutar los distintos estados del comando si es que lo necesita.
 * Hasta devolver un finish.
 */
int *execute_command(t_handler *s)
{
	int i;
	int j;
	t_exec *exec;

	i = -1;
	j = 0;
	exec = s->exec;
	while (++i < s->len_exec)
	{
		if (exec[i].func[0][0])
		{
			if (j == s->len_exec - 1)
			{
				exec[i].file.input = s->fd[0];
				exec[i].file.output = 1;
				if (exec[i].cmd[1].cmd)
					exec[i].cmd[1].towait = 1;
			}
			if (j < (s->len_exec) && j > 0)
			{
				// if (s->exec[s->info->i].op == PIPE)
				// close(s->exec[s->info->i].file.input);
				exec[i].file.input = s->fd[0];
				pipe(s->fd);
				exec[i].file.output = s->fd[1];
			}
			j++;
			if (j == 1 && 1 != s->len_exec)
				exec[i].file.output = s->fd[1];
			else if (j == s->len_exec)
				exec[i].file.output = 1;
			exec[i].state = exec[i].func[EMPTY][EMPTY](&(exec[i]));
			if (exec[i].state[1] != 0)
				exec[i].status = exec[i].state[1];
			if (exec[i].state[0] != 0)
				exec[i].status = exec[i].state[0];
			exec[i].handler->code = exec[i].status;
		}
		//        while (exec[i].func[exec[i].state[0]][exec[i].state[1]])
		//            exec->state = exec[i].func[exec[i].state[0]][exec[i].state[1]](&(exec[i]));
		// if (exec[i + 1].cmd)
		//    exec[i + 1].state = exec[i].state;
	}

	return (exec[i].state);
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
	s->state[0] = 0;
	s->state[1] = 0;
	s->state[2] = 0;
	s->info->i = 0;
	s->info->oid = 30;
	s->exec = 0;
	if (pipe(s->fd) == -1)
		return s;
	s->exec = malloc(sizeof(t_exec) * (ft_sarrsize(s->info->tokens) + 1));
	if (!s->exec)
		return (s);
	// Proceso los tokens y configuro el entorno para la ejecucion
	handler_execute(s);
	int i;
	i = 0;
	if (s->w_cmd)
	{
		while (s->w_cmd[i].pid)
			i++;
		s->n_pids = i;
	}
	if (info.len_tokens <= 1)
		return s;
	// Ejecuto los comandos en base a las configuraciones.
	execute_command(s);
	return (s);
}
t_handler *ft_clear(t_handler *s)
{

	s->info->tokens = 0;
	s->state[0] = 0;
	s->state[1] = 0;
	s->state[2] = 0;
	s->len_exec = 0;
	s->info = 0;
	s->line = NULL;
	s->fd[0] = -1;
	s->fd[1] = -1;
	s->exec = 0;
	return (s);
}
t_handler *ft_exec(t_handler *s)
{
	return (s);
}