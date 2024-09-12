#include "../headers/minishell.h"

void ft_conf_less(t_handler *s, int i)
{
    char *line;
    int j = s->info->i;
    // int fd;
    s->exec[s->info->i].handler = s;
    s->exec[s->info->i].cmd = ft_calloc(sizeof(t_cmd), 3);
    s->exec[s->info->i].op = LESS;
    s->exec[s->info->i].state = ft_calloc(sizeof(int), 2);
    s->exec[s->info->i].state[0] = 0;
    s->exec[s->info->i].state[1] = 0;
    s->exec[s->info->i].cmd[0].cmd = 0;
    s->exec[s->info->i].file.input = 0;
    s->exec[s->info->i].file.output = 1;
    if (s->info->oid != (i - 1))
    {
        s->exec[s->info->i].cmd[0].line = s->info->tokens[i - 1];
        s->exec[s->info->i].cmd[0].cmd = do_exec(s->info->tokens[i - 1], s->env);
        pipe(s->exec[s->info->i].cmd[0].fd_aux);
    }
    else
        s->exec[s->info->i].state[0] = 1;
    if (s->info->oid != (i + 1))
    {
        line = s->info->tokens[i + 1];
        line = ft_strtrim(line, "\"");
        s->exec[s->info->i].file.dir_file = line; // Tengo que liberar la linea
        s->exec[s->info->i].state[1] = 0;
    }
    else
        s->exec[s->info->i].state[1] = 1;

    // Lo que pretendo es que si tengo multiples redirecciones <, las anteriores no se ejecuten y muevan el
    // comando a la siguiente redireccion, para que me quede solo con la ultima redireccion.
    while (s->exec[--j].op == LESS)
    {
        if (s->exec[j].state[0] == 0)
        {
            s->exec[s->info->i].cmd[0].line = s->exec[j].cmd[0].line;
            s->exec[s->info->i].cmd[0].cmd = s->exec[j].cmd[0].cmd;
            s->exec[s->info->i].cmd[0].fd_aux[0] = (s->exec[j].cmd[0].fd_aux[0]);
            s->exec[s->info->i].cmd[0].fd_aux[1] = (s->exec[j].cmd[0].fd_aux[1]);
            s->exec[s->info->i].state[0] = 0;
        }
        // Tambien puedo borrar s->exec[j] ya que no lo volvere a utilizar.
    }
    s->info->oid = i + 1;
    s->exec[s->info->i].cmd[2].cmd = NULL;
    // En caso de que los dos estados o uno solo no se pueda ejecutar deberia devolver un error, por tanto llamar a otra funcion
    s->exec[s->info->i].func[0][0] = ft_exec_less;
    s->info->i++;
}
