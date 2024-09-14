#include "../headers/minishell.h"

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
    a->block[a->info->i].status = 0;
    while (a->info->tokens[++i])
    {

        a->state[2] = idstr(a->operators, a->info->tokens[i]);
        if (a->state[2] == 9 || a->state[2] == 10)
        {
            a->block[a->info->i].priority = 1;
            a->state[2] = 0;
        }
        if (a->state[1] == NOT_OPERATOR)
        {
            if (do_exec(a->info->tokens[i - 1], a->env) && a->state[2] == EMPTY)
                a->state[1] = UNIQ_COMMAND;
        }
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

        exec[i_exec].handler = a;
        if ((a->state[0] == OP_PIPE || a->state[1] == OP_PIPE) && (a->state[2] == OP_HEREDOC || a->state[2] == OP_APPEND || a->state[2] == OP_GREATER || a->state[2] == OP_LESS))
        {
            a->info->oid = -1;
            if (exec[i_exec - 1].op)
                exec[i_exec - 1].state[1] = 2;
        }
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

void init_handler(t_handler *s)
{
    operators_init(s);
    builtings_init(s);
    tactions_handler_init(s);
    tactions_builtins_init(s);
    s->code = 0;
}

t_handler *ft_config(t_handler *s)
{
    int i;
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
    if (s->info->len_tokens <= 1)
        return s;
    return s;
}