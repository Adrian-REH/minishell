#include "../src/headers/minishell.h"

t_exec *add_exec(t_exec *execs, t_exec exec)
{
    int i;

    i = 0;
    if (execs == NULL)
    {
        printf("calloc\n");
        execs = ft_calloc(sizeof(t_exec), 2);
        execs[0] = exec;
        execs[1].op = 0;
        return execs;
    }
    while (execs[i].op)
        i++;
    printf("realloc: %d\n", i);
    execs = ft_realloc(execs, sizeof(t_exec) * (i + 2));
    execs[i++] = exec;
    return execs;
}