
#include "headers/minishell.h"

char **toarr(char **argenv)
{
    char **arr;
    int i;

    i = -1;
    arr = malloc(sizeof(char *) * (ft_sarrsize(argenv) + 1));
    while (argenv[++i])
        arr[i] = ft_strdup(argenv[i]);
    return arr;
}

void sigint_handler(int signum)
{
    if (signum == SIGINT) {
        printf("\n"); // Hacemos un salto de línea para que no quede el prompt cortado
        rl_replace_line("", 0);  // Reemplaza la línea actual por una vacía
        rl_on_new_line();  // Le decimos a readline que comenzamos una nueva línea
        rl_redisplay();  // Vuelve a mostrar el prompt
    }
}
int main(int argc, char **argv, char **argenv)
{
    (void)argv;
    (void)argenv;
    (void)argc;
    char *comand;
    t_handler handler;
    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);


	handler.env = toarr(argenv);
    // struct t_rule (*seg[1])(struct t_rule pedidos) = {ft_parser};
    handler.seg[0] = ft_parser;
    handler.seg[1] = ft_config;
    handler.seg[2] = ft_execute;
    handler.seg[3] = ft_clear;
    // handler.seg[2] = ft_handler_exceptions;
    //  inicializar info aqui y liberar luego
    init_handler(&handler);
    int i;
    int status;
    while (1)
    {
        comand = readline("minishell> ");
        if (comand == NULL)//SI ace CTRL+D se queda aqui, por ende puedo enviar o redirigir a liberar todo
            break;
        handler.line = comand;
        if (comand && *comand)
            add_history(comand);

        handler.seg[0](&handler);
        handler.seg[1](&handler);
        handler.seg[2](&handler);
        handler.seg[3](&handler);
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
