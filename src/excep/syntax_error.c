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

int	syntax_error(char *operator, int type)
{
	if (type == 2)
		ft_putstr_fd(" syntax error near unexpected token `", 2);
	ft_putstr_fd(operator, 2);
	ft_putstr_fd("'\n", 2);
	save_error(2);
	return (2);
}

int	ambiguous_redirect(char *operator, int type)
{
	(void)operator;
	(void)type;
	ft_putstr_fd(" ambiguous redirect\n", 2);
	save_error(1);
	return (1);
}

int	empty_wildcard(char *operator, int type)
{
	(void)operator;
	(void)type;
	save_error(2);
	return (2);
}
