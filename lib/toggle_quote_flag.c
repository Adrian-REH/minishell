/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:11:53 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 06:33:47 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/headers/minishell.h"

int	toggle_quote_flag(int *flag, char *result, int i)
{
	if (result[i] == '\'')
	{
		if (*flag == 0)
			*flag = 2;
		else
			*flag = 0;
		return (1);
	}
	if (result[i] == '\"')
	{
		if (*flag == 1)
			*flag = 2;
		else
			*flag = 1;
		return (1);
	}
	return (0);
}
int	toggle_flag_printquote(int *flag, char *result, int i)
{
	if (result[i] == '\'')
	{
		if (*flag == 1 && ft_strchr(result + i, '\"'))
			printf("\'");
		if (*flag == 0)
			*flag = 2;
		else
			*flag = 0;
		return (1);
	}
	if (result[i] == '\"')
	{
		if (!*flag && ft_strchr(result + i, '\''))
			printf("\"");
		if (*flag == 1)
			*flag = 2;
		else
			*flag = 1;
		return (1);
	}
	return (0);
}
