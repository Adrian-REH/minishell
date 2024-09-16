/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:15:03 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 08:23:43 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

void sigint_handler(int signum)
{
	if (signum == SIGINT) {
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
int	main(int argc, char **argv, char **argenv)
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

	handler.env = duparr(argenv);
	handler.seg[0] = ft_parser;
	handler.seg[1] = ft_config;
	handler.seg[2] = ft_execute;
	handler.seg[3] = ft_clear;
	init_handler(&handler);
	int i;
	int status;
	while (1)
	{
		comand = readline("minishell> ");
		if (comand == NULL)
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
