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

void	sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	main(int argc, char **argv, char **argenv)
{
	char				*comand;
	t_handler			handler;
	struct sigaction	sa;

	(void)argc;
	(void)argv;
	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	handler.env = duparr(argenv);
	init_handler(&handler);
	while (1)
	{
		comand = readline("minishell> ");
		if (comand == NULL)
			break ;
		handler.line = comand;
		if (comand && *comand)
			add_history(comand);
		handler.seg[0](&handler);
		(handler.seg[1](&handler), handler.seg[2](&handler));
		(handler.seg[3](&handler), handler.seg[4](&handler));
	}
}
