#include "../src/headers/minishell.h"

int	ft_isbuiltin(char **builtins, char *token)
{
	int	i;

	i = -1;

	if ((ft_strnstr(token, builtins[0], ft_strlen(token)) == 0 ) && ft_strnstr(token, "-n", ft_strlen(token)))
		return (1);
	while (builtins[++i])
		if (ft_strnstr(token, builtins[i], ft_strlen(token)))
			return (i);
	return (NOT_OPERATOR);
}
