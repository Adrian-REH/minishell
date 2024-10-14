/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:15:03 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/24 18:06:37 by adherrer         ###   ########.fr       */
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
		save_error(130);
	}
	if (signum == SIGQUIT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		save_error(131);
	}
	if (signum == SIGKILL)
		save_error(1000);
}

void	init_handler(t_handler *s)
{
	s->seg[0] = ft_parser;
	s->seg[1] = ft_config;
	s->seg[2] = ft_execute;
	s->seg[3] = ft_subprocess;
	s->seg[4] = ft_clear;
	operators_init(s);
	builtings_init(s);
	tactions_errors_init(s);
	tactions_handler_init(s);
	tactions_builtins_init(s);
	s->code = 0;
}

int	main(int argc, char **argv, char **argenv)
{
	char				*comand;
	t_handler			handler;
	struct sigaction	sa;

	(void)argc;
	(void)argv;
	sa.sa_handler = sigint_handler;
	sa.sa_flags = (sigemptyset(&sa.sa_mask), 0);
	(sigaction(SIGINT, &sa, NULL), sigaction(SIGQUIT, &sa, NULL));
	(sigaction(SIGKILL, &sa, NULL), ft_bzero(&handler, sizeof(t_handler)));
	handler.env = (init_handler(&handler), duparr(argenv));
	while (1)
	{
		comand = (save_error(handler.code), readline("minishell> "));
		if (comand == NULL)
			break ;
		handler.line = comand;
		if (comand && *comand)
			add_history(comand);
		handler.seg[0](&handler);
		(handler.seg[1](&handler), handler.seg[2](&handler));
		(handler.seg[3](&handler), handler.seg[4](&handler));
	}
	rl_cleanup_after_signal();
	handler.seg[4](&handler);
	ft_free_p2(handler.env);
	handler.env = NULL;
	ft_free_p2(handler.builtins);
	handler.builtins = NULL;
	ft_free_p2(handler.operators);
	handler.operators = NULL;
}
