#include "../headers/minishell.h"

int ft_strlen(const char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return i;
}

int idx(char *alphabet[], char c)
{
    int i;

    i = -1;
    while (alphabet[++i])
        if (ft_chrpos(alphabet[i], c, 0) != -1)
            return (i);
    return (i);
}

int idstr(char *alphabet[], char *str)
{
    int i;

    i = -1;
    while (alphabet[++i])
        if (strcmp(alphabet[i], str) == 0)
            return (i);
    return (NOT_OPERATOR);
}
int evaluate(t_automata *a)
{
    a->ostate = 0;
    a->i = -1;
    while (++a->i < ft_strlen(a->str))
    {
        printf("---------------------\nlast state: %d |find: %d\n", a->state, idx(a->alphabet, a->str[a->i]));
        a->state = a->get_state(a->state, idx(a->alphabet, a->str[a->i]));
        printf("new state: %d\n", a->state);
        if (a->fsa[a->state])
            a->fsa[a->state](a, a->data);
        if (a->fta[a->ostate][a->state])
            a->fta[a->ostate][a->state](a, a->data);
        a->ostate = a->state;
    }
    return (a->state);
}

int *handler_execute(t_handler *a)
{
    int i = -1;

    while (a->info->tokens[++i])
    {
        a->exec[i].handler = a;
        a->exec[i].priority = 0;
        a->exec[i].file.input = a->fd[0];
        a->exec[i].file.output = a->fd[1];
        a->state[2] = idstr(a->operators, a->info->tokens[i]);
        printf("[0]%d|[1]%d|[2]%d\n", a->state[0], a->state[1], a->state[2]);
        if (a->fta[a->state[0]][a->state[1]][a->state[2]])
            a->fta[a->state[0]][a->state[1]][a->state[2]](a, i - 1);
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
void init_handler(t_handler *s, void *data)
{
    operators_init(s);
    tactions_handler_init(s);
    s->info = data;
    if (pipe(s->fd) == -1)
        return;
    s->exec = malloc(sizeof(t_exec) * (ft_sarrsize(s->info->tokens) + 1));
    if (!s->exec)
        return;
    s->state[0] = 0;
    s->state[1] = 0;
    s->state[2] = 0;
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
    t_exec *exec;

    i = -1;
    while (++i < s->info->len_tokens)
    {
        exec = s->exec;
        exec[i].state = malloc(sizeof(int) * 2);
        exec[i].state[0] = 0;
        exec[i].state[1] = 0;

        if (exec[i].func[0][0])
            exec[i].state = exec[i].func[0][0](&(exec[i]));
        while (exec[i].func[exec[i].state[0]][exec[i].state[1]])
            exec->state = exec[i].func[exec[i].state[0]][exec[i].state[1]](&(exec[i]));
        free(exec[i].state);
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
    finalstate = evaluate(&a);
    if (finalstate > a.errorlen)
        get_token(&a, &info);
    s->code = finalstate;

    // LIMPIAR PARA QUE NO TENGAN ESPACIOS NI ADELANTE NI ATRAS
    ft_sarrprint(info.tokens);
    // Execution init
    info.len_tokens = ft_sarrsize(info.tokens);
    if (info.len_tokens == 0)
        return s;
    init_handler(s, &info);
    handler_execute(s);
    execute_command(s);
    return (s);
}
