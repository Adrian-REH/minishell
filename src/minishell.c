
#include "headers/minishell.h"

int main(int argc, char **argv, char **argenv)
{
    (void)argv;
    (void)argenv;
    (void)argc;
    char *comand;
    t_handler handler;

    handler.env = argenv;
    // struct t_rule (*seg[1])(struct t_rule pedidos) = {ft_parser};
    handler.seg[0] = ft_parser;
    handler.seg[1] = ft_clear;
    // inicializar info aqui y liberar luego
    init_handler(&handler);
    int i;
    int status;

    while (1)
    {
        comand = readline("minishell> ");
        handler.line = comand;
        if (comand && *comand)
            add_history(comand);
        if (strcmp(comand, "exit") == 0)
            break;
        if (strcmp(comand, "clear") == 0)
            clear_history();
        handler.seg[0](&handler);
        handler.seg[1](&handler);
        if (handler.pids)
        {
            i = -1;
            while (handler.pids[++i])
            {
                pid_t result = waitpid(handler.pids[i], &status, WNOHANG);
                if (result == handler.pids[i])
                {
                    printf("[%d] Done\n", i + 1);
                    handler.pids[i] = 0;
                }
            }
        }
    }
    (void)handler;
}
