/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:40:38 by adherrer          #+#    #+#             */
/*   Updated: 2024/08/04 20:02:21 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_print_error(char *title, int code, char *line)
{
	char *str;
	char *cmd;

	if (line)
		cmd = ft_strtrim(line, " ");
	else
		cmd = ft_strdup("");
	str = ft_strjoin(title, cmd);
	if (!str)
		exit(1);
	ft_putendl_fd(str, 2);
	free(str);
	free(cmd);
	exit(code);
}
