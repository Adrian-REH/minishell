/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle_quote_flag.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantill <msantill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:11:16 by adherrer          #+#    #+#             */
/*   Updated: 2024/10/20 17:54:10 by msantill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/headers/minishell.h"

int	toggle_quote_flag(int *flag, char *result, int i)
{
	if (result[i] == '\'')
	{
		if (!*flag)
			*flag = 2;
		else if (*flag == 2)
			*flag = 0;
		return (1);
	}
	if (result[i] == '\"')
	{
		if (!*flag)
			*flag = 1;
		else if (*flag == 1)
			*flag = 0;
		return (1);
	}
	return (0);
}

int	toggle_flag_printquote(int *flag, char *result, int i)
{
	if (result[i] == '\'')
	{
		if (!*flag)
			*flag = 2;
		else if (*flag == 1)
			printf("\'");
		else if (*flag == 2)
			*flag = 0;
		return (1);
	}
	if (result[i] == '\"')
	{
		if (!*flag)
			*flag = 1;
		else if (*flag == 2)
			printf("\"");
		else if (*flag == 1)
			*flag = 0;
		return (1);
	}
	return (0);
}

