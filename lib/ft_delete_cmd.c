#include "../src/headers/minishell.h"

t_cmd *delete_cmd(t_cmd *cmds, int i)
{
    int j;

    j = i;
    while (cmds[j].pid)
    {
        cmds[j] = cmds[j + 1];
        j++;
    }
    cmds[j].pid = 0;
    return cmds;
}