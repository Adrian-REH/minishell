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

struct signal_info {
    int signal_num;
};

int	ft_static(int j)
{
	static int i = 0;

	if (j != 0)
		i = j;
	return (i);
}


void	sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		get_error(signum, 0);
		//Tengo que hacer que el block se libere
	}
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
	sa.sa_handler  = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	printf("Bienvenido a Minishell\n");
	ft_bzero(&handler, sizeof(t_handler));
	handler.env = duparr(argenv);
	init_handler(&handler);
	while (1)
	{
		//if (get_error(0))
		//	handler.seg[4](&handler);
		comand = readline("minishell> ");
		get_error(0, 1);
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
