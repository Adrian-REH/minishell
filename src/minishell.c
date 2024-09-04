
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
        if (handler.w_cmd)
        {
            i = -1;
            while (handler.w_cmd[++i].pid)
            {
                pid_t result = waitpid(handler.w_cmd[i].pid, &status, WNOHANG);
                if (result == handler.w_cmd[i].pid)
                {
                    printf("[%d] Done\t\t\t%s\n", i + 1, handler.w_cmd[i].cmd[0]);
                    handler.n_pids--;
                    handler.w_cmd = delete_cmd(handler.w_cmd, i);
                }
            }
        }
    }
    (void)handler;
}
