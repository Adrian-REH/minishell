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

int	keep_content_byspace(char **tkn, int i, char *space_pos)
{
	char	*temp;

	temp = tkn[i - 2];
	tkn[i - 2] = ft_strjoin(temp, space_pos);
	if (!tkn[i - 2])
		return (-1);
	free(temp);
	temp = tkn[i];
	tkn[i] = ft_substr(tkn[i], 0, ft_strlen(tkn[i]) - ft_strlen(space_pos));
	if (!tkn[i])
		return (-1);
	tkn[i] = ft_strdelchr(tkn[i], '\"');
	free(temp);
	return (1);
}
