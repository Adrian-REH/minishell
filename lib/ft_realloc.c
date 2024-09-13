#include "../src/headers/minishell.h"

void *ft_realloc(void *ptr, size_t size)
{
    void *new;

    new = malloc(size);
    if (!new)
        return NULL;
    if (ptr)
    {
        ft_memcpy(new, ptr, size);
        free(ptr);
    }
    return new;
}