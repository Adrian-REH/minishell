/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:11:25 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 06:32:34 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/headers/minishell.h"

int	handler_keep_content(char **tkn, int i)
{
	char	*space_pos;

	space_pos = ft_strchr(tkn[i], ' ');
	if (tkn[i][0] == '\"' && space_pos)
	{
		if (keep_content_byquote(tkn, i) == -1)
			return (-1);
		else
			return (1);
	}
	if (space_pos)
	{
		if (keep_content_byspace(tkn, i, space_pos) == -1)
			return (-1);
		else
			return (1);
	}
	return (0);
}
