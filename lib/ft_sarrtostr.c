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

char	*ft_sarrtostr(char **arr, char *sep)
{
	char	*str;
	char	*tmp;
	int		i;

	i = -1;
	str = ft_strdup("");
	while (arr[++i])
	{
		tmp = str;
		str = ft_strjoin(tmp, arr[i]);
		tmp = (free(tmp), str);
		str = ft_strjoin(tmp, sep);
		free(tmp);
	}
	return (str);
}
