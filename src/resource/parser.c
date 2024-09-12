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
	t_exec *exec;
	int i_exec;

	// a->exec[0].file.input = 0;
	a->block[a->info->i].op = BLOCK_EMPTY;
	a->block[a->info->i].isnext = 0;
	a->block[a->info->i].len_exec_prev = 0;
	a->block[a->info->i].len_exec_next = 0;
	a->block[a->info->i].len_exec = 0;
	a->block[a->info->i].prev_exec = 0;
	a->block[a->info->i].next_exec = 0;
	while (a->info->tokens[++i])
	{
		if (a->block[a->info->i].isnext)
		{
			a->block[a->info->i].next_exec = ft_realloc(a->block[a->info->i].next_exec, sizeof(t_exec) * (a->block[a->info->i].len_exec_next + 1));
			exec = a->block[a->info->i].next_exec;
			i_exec = a->block[a->info->i].len_exec_next;
		}
		else
		{
			a->block[a->info->i].prev_exec = ft_realloc(a->block[a->info->i].prev_exec, sizeof(t_exec) * (a->block[a->info->i].len_exec_prev + 1));
			i_exec = a->block[a->info->i].len_exec_prev;
			exec = a->block[a->info->i].prev_exec;
		}

		a->state[2] = idstr(a->operators, a->info->tokens[i]);
		exec[i_exec].handler = a;
		if (a->state[2] == 9)
		{
			a->block[a->info->i].priority = 1;
			a->state[2] = 0;
		}
		else if (a->state[2] == 10)
		{
			a->block[a->info->i].priority = 1;
			a->state[2] = 0;
		}
		// Verifico si es un cmd o un file o si es un idstr

		if (a->state[1] == NOT_OPERATOR)
		{
			if (do_exec(a->info->tokens[i - 1], a->env) && a->state[2] == EMPTY)
				a->state[1] = UNIQ_COMMAND;
		}
		if (a->state[0] == OP_PIPE && (a->state[2] == OP_HEREDOC || a->state[2] == OP_GREATER))
		{
			a->info->oid = -1;
			exec[i_exec - 1].state[1] = 2;
		}
		// VErifico si el cmd es un built-in y que tipo es
		if (a->fta[a->state[0]][a->state[1]][a->state[2]])
		{
			j++;
			a->fta[a->state[0]][a->state[1]][a->state[2]](a, i - 1);
			if (a->state[1] == OP_AND || a->state[1] == OP_OR)
				a->state[1] = 0;
		}
		a->block[a->info->i].len_exec = j;
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
/* int *execute_command(t_handler *s)
{
	int i;
	int j;
	t_exec *exec;

	i = -1;
	j = 0;
	exec = s->exec;
	// Debo ejecutar los anteriores a AND y OR y ante el resultado de estos ejecutar los siguientes
	// Para ello debo posicionarme donde hay un primer AND u OR y ejecutar los anteriores de izq a Derecha.
	while (++i < s->len_exec)
	{
		if (exec[i].func[0][0])
		{
			if ((j == s->len_exec - 1) && exec[i].op == PIPE)
			{
				exec[i].file.input = s->fd[0];
				exec[i].file.output = 1;
				if (exec[i].cmd[1].cmd)
					exec[i].cmd[1].towait = 1;
			}
			if (j < (s->len_exec) && j > 0 && (exec[i].op == PIPE || exec[i].op == GREATER || exec[i].op == LESS))
			{
				exec[i].file.input = s->fd[0];
				close(s->fd[1]);
				pipe(s->fd);
				exec[i].file.output = s->fd[1];
			}
			j++;
			if (j == 1 && 1 != s->len_exec && (exec[i].op == PIPE || exec[i + 1].op == PIPE || exec[i].op == LESS))
			{
				exec[i].file.output = (s->fd[1]);
			}
			else if (j == s->len_exec && (exec[i].op == PIPE || exec[i].op == HEREDOC || exec[i].op == LESS))
				exec[i].file.output = 1;
			exec[i].state = exec[i].func[EMPTY][EMPTY](&(exec[i]));
			exec[i].handler->code = exec[i].status;
		}
	}
	return (exec[i].state);
}
 */

int execute_cmds(t_block *b, int isnext)
{
	int i;
	int j;
	t_exec *exec;

	i = -1;
	j = 0;
	if (isnext)
	{
		exec = b->next_exec;
		b->len_exec = b->len_exec_next;
	}
	else
	{
		exec = b->prev_exec;
		b->len_exec = b->len_exec_prev;
	}
	// Debo ejecutar los anteriores a AND y OR y ante el resultado de estos ejecutar los siguientes
	// Para ello debo posicionarme donde hay un primer AND u OR y ejecutar los anteriores de izq a Derecha.
	printf("len_exec: %d\n", b->len_exec);
	while (++i < b->len_exec)
	{
		if (exec[i].func[0][0])
		{
			if ((j == b->len_exec - 1) && exec[i].op == PIPE)
			{
				exec[i].file.input = b->fd[0];
				exec[i].file.output = 1;
				if (exec[i].cmd[1].cmd)
					exec[i].cmd[1].towait = 1;
			}
			if (j < (b->len_exec) && j > 0 && (exec[i].op == PIPE || exec[i].op == GREATER || exec[i].op == LESS))
			{
				exec[i].file.input = b->fd[0];
				close(b->fd[1]);
				pipe(b->fd);
				exec[i].file.output = b->fd[1];
			}
			j++;
			if (j == 1 && 1 != b->len_exec && (exec[i].op == PIPE || exec[i + 1].op == PIPE || exec[i].op == LESS))
			{
				exec[i].file.output = (b->fd[1]);
			}
			else if (j == b->len_exec && (exec[i].op == PIPE || exec[i].op == HEREDOC || exec[i].op == LESS))
				exec[i].file.output = 1;
			exec[i].state = exec[i].func[EMPTY][EMPTY](&(exec[i]));
			b->status = exec[i].status;
		}
	}
	return (b->status);
}

int *block_execute(t_handler *s)
{
	int i;

	i = -1;
	// Debo ejecutar los anteriores a AND y OR y ante el resultado de estos ejecutar los siguientes
	while (++i < s->len_block)
	{
		if (s->block[i].len_exec_prev)
		{
			printf("block[%d].prev_op: %d\n", i, s->block[i].op);
			execute_cmds(&(s->block[i]), 0);
			if (s->block[i].status == 1 && s->block[i].op == AND)
				break;
			else if (s->block[i].status == 0 && s->block[i].op == OR)
			{
				if (s->block[i].priority)
					continue;
				break;
			}
		}
		else
		{
			// Devo verificar el estado del blocke anterior y validarlo con el tipo de operador en el que estoy.
		}
		if (s->block[i].len_exec_next)
		{
			printf("block[%d].next_op: %d\n", i, s->block[i].op);
			execute_cmds(&(s->block[i]), 1);
			if (s->block[i].status == 1 && s->block[i + 1].op == AND)
			{
				if (s->block[i].priority && s->block[i + 1].op == OR)
					continue;
				break;
			}
			else if (s->block[i].status == 0 && s->block[i + 1].op == OR)
			{
				if (s->block[i].priority && s->block[i + 1].op == OR)
					continue;
				break;
			}
		}
	}
	return (NULL);
}

t_handler *ft_parser(t_handler *s)
{
	(void)s;
	int i;
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

	i = -1;
	s->len_block = 1;
	while (s->info->tokens[++i])
	{
		if (idstr(s->operators, s->info->tokens[i]) == 8)
		{
			s->len_block++;
		}
		else if (idstr(s->operators, s->info->tokens[i]) == 7)
		{
			s->len_block++;
		}
	}
	s->block = malloc(sizeof(t_block) * (s->len_block));
	if (!s->block)
		return (s);
	s->block->op = BLOCK_EMPTY;
	s->info->oid = 30;
	if (pipe(s->block->fd) == -1)
		return s;
	// Proceso los tokens y configuro el entorno para la ejecucion
	handler_execute(s);
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

	block_execute(s);
	// execute_command(s);
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
t_handler *ft_exec(t_handler *s)
{
	return (s);
}