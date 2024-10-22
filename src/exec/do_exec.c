/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:12:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 08:24:10 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	evaluate_quotes(t_automata *a)
{
	a->ostate = 0;
	a->i = -1;
	while (++a->i < ft_strlen(a->str) && a->state != 11)
	{
		a->state = a->get_state(a->state, idx(a->alphabet, a->str[a->i]));
		if (a->ostate == 14 && a->state == 2)
			get_token(a, a->data);
		else if (a->ostate == 13 && a->state == 2)
			get_token(a, a->data);
		else if (a->ostate == 13 && a->state == 1)
			get_token(a, a->data);
		else if (a->ostate == 14 && a->state == 1)
			get_token(a, a->data);
		a->ostate = a->state;
	}
	if (a->state > 11)
		get_token(a, a->data);
	return (a->state);
}

char	**process_arr_and_tmp(char **arr)
{
	char	**tmp;

	if (!ft_strchr(arr[0], '"') && !ft_strchr(arr[0], '\''))
	{
		tmp = ft_split(arr[0], ' ');
		if (tmp && arr)
		{
			tmp = ft_sarrjoin(tmp, arr + 1);
			ft_free_p2(arr);
			return (tmp);
		}
	}
	return (arr);
}

void	remove_quotes_from_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
	{
		if (*arr[i] == '"')
			ft_strdelchr(arr[i], '\"');
		if (*arr[i] == '\'')
			ft_strdelchr(arr[i], '\'');
	}
}

char	**ft_resolve_quotes(char *line)
{
	char		**arr;
	t_automata	a;
	t_data		info;

	arr = NULL;
	ft_bzero(&a, sizeof(t_automata));
	ft_bzero(&info, sizeof(t_data));
	automata_init(&a, &info);
	a.str = line;
	evaluate_quotes(&a);
	arr = duparr(info.tokens);
	if (!arr)
		return (NULL);
	ft_free_p2(info.tokens);
	arr = process_arr_and_tmp(arr);
	remove_quotes_from_arr(arr);
	ft_free_p2(a.alphabet);
	ft_free_p2(a.errors);
	return (arr);
}

char	**do_exec(char *line, char **env)
{
	char	*cmd;
	char	**command;

	if (!line)
		return (NULL);
	command = ft_resolve_quotes(line);
	if (!command)
		return (NULL);
	if (!command)
		return (perror("Memory error: "), NULL);
	if (*command == 0)
		return (ft_free_p2(command), NULL);
	if ((access(command[0], 0 | 1) == 0) && ft_strnstr(command[0], "./", 2))
		return (command);
	else if (access(command[0], 0 | 1) != 0 && ft_strchr(command[0], '/'))
		return (command);
	else
	{
		cmd = get_path(command[0], env);
		if (cmd != NULL && ft_strcmp(cmd, command[0]) != 0)
			command[0] = (free(command[0]), cmd);
		return (command);
	}
	return (command);
}
