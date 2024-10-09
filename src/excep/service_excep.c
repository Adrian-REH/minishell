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

static int	storage_error(int error, int change)
{
	static int	err;

	if (change)
		err = error;
	return (err);
}

int	save_error(int error)
{
	return (storage_error(error, 1));
}

int	get_error(void)
{
	return (storage_error(0, 0));
}

void	parser_error(t_handler *s, int error)
{
	if (s->a->errors[error])
	{
		ft_putstr_fd(" syntax error near unexpected token '", 2);
		ft_putstr_fd(s->a->errors[error], 2);
		ft_putstr_fd("'\n", 2);
	}
	save_error(2);
	s->code = 2;
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
