/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keep_content_byquote.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:11:25 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/21 16:49:16 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/headers/minishell.h"

int	keep_content_byquote(char **tkn, int i)
{
	char	*temp;
	char	*q_pos;

	temp = tkn[i - 2];
	q_pos = ft_strchr(tkn[i] + 1, '\"');
	if (!q_pos)
		return (1);
	tkn[i - 2] = ft_strjoin(temp, q_pos + 1);
	if (!tkn[i - 2])
		return (-1);
	free(temp);
	temp = ft_substr(tkn[i] + 1, 0, ft_strlen(tkn[i]) - ft_strlen(q_pos) - 1);
	if (!temp)
		return (-1);
	free(tkn[i]);
	tkn[i] = temp;
	tkn[i] = ft_strdelchr(tkn[i], '\"');
	return (1);
}
