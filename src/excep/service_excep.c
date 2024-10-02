/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service_excep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:12:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 06:13:17 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	get_error(int type, int change)
{
	static int	code;

	if (type == 0 && change == 0)
		return (code);
	else if (change != 0)
		code = type;
	else
		code = type;
	return (code);
}

void	parser_error(t_handler *s, int error)
{
	if (s->a->errors[error])
	{
		ft_putstr_fd(" syntax error near unexpected token '", 2);
		ft_putstr_fd(s->a->errors[error], 2);
		ft_putstr_fd("'\n", 2);
	}
	get_error(2, 0);
	s->code = 2;
}

int	syntax_error(char *operator, int type)
{
	if (type == 2)
		ft_putstr_fd(" syntax error near unexpected token '", 2);
	else if (type == 1)
	{
		ft_putstr_fd(" ambiguous redirect", 2);
		return (type);
	}
	ft_putstr_fd(operator, 2);
	ft_putstr_fd("'\n", 2);
	get_error(2, 0);
	return (2);
}

void	ft_execute_exception(t_cmd *cmd)
{
	(void)cmd;
}

void	ft_exeption_fd(int inp, int out, int fd[2])
{
	if (inp != 0 && inp != 0)
		close(inp);
	if (out != 0 && out != 1)
		close(out);
	if (fd[0] != 0 && fd[1] != 0)
	{
		close(fd[0]);
		close(fd[1]);
	}
	ft_print_error(strerror(errno), 1, NULL);
}
