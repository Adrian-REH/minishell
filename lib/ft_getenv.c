/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:11:22 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 06:28:19 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/headers/minishell.h"

char	*ft_getenv(t_cmd *cmd, char *str)
{
	int	i;

	i = -1;
	while (cmd->handler->env[++i])
	{
		if (!ft_strncmp(cmd->handler->env[i], str, ft_strlen(str)))
			return (cmd->handler->env[i] + ft_strlen(str) + 1);
	}
	return (NULL);
}
