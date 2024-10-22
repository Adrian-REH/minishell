/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrpos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:11:19 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 06:28:20 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/headers/minishell.h"

char	*concat_and_release(char *val, char *result, char **arr)
{
	char	*tmp;

	tmp = result;
	if (val)
	{
		result = ft_strjoin(tmp, val);
		val = (free(tmp), (tmp = NULL), free(val), NULL);
	}
	else
	{
		result = ft_strjoin(tmp, *arr);
		free(tmp);
	}
	if (!result && val)
		return (free(val), NULL);
	return (result);
}
