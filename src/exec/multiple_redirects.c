/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:12:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/24 18:27:01 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	count_redirects(t_exec *e, int i)
{
	int		j;

	j = i;
	while (j >= 0 && (e[j].op <= 8 && e[j].op >= 5))
		j--;
	j++;
	return (j);
}

static void	infile_open(t_exec *e, int i, int *j)
{
	printf("AQUI\n");
	e[i].file.input = open(e[*j].file.idfile, O_RDONLY, 0644);
	if (e[i].file.input == -1)
		(ft_print_error(strerror(errno), 1, NULL));
	e[i].file.idfile = (close(e[i].file.input), e[*j].file.idfile);
	(*j)++;
}

static void	outfile_open(t_exec *e, int i, int *j)
{
	e[i].file.output = open(e[*j].file.odfile, 1 | O_CREAT | O_APPEND, 0644);
	if (e[i].file.output == -1)
		(ft_print_error(strerror(errno), 1, NULL));
	close(e[i].file.output);
	if (!e[i].file.odfile)
		e[i].file.odfile = e[*j].file.odfile;
	(*j)++;
}

void	get_execute_files(t_exec *e, int i)
{
	int		j;

	j = count_redirects(e, i);
	while (j < (i + 1) && (e[j].op <= 8 && e[j].op >= 5))
	{
		if (e[j].op == LESS)
			infile_open(e, i, &j);
		else if (e[j].op != 6)
			outfile_open(e, i, &j);
		else
			j++;
	}
}
