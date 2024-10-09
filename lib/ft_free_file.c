/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 01:44:59 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/23 01:45:26 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/headers/minishell.h"

void	*ft_free_file(t_file *file)
{
	if (is_fd_open(file->input) && file->input != 0)
		close(file->input);
	if (is_fd_open(file->output) && file->output != 1)
		close(file->output);
	if (is_fd_open(file->fd_aux[0]) && file->fd_aux[0] != 0)
		close(file->fd_aux[0]);
	if (is_fd_open(file->fd_aux[1]) && file->fd_aux[1] != 1)
		close(file->fd_aux[1]);
	if (file->content)
		ft_free_p2(file->content);
	free(file->idfile);
	free(file->odfile);
	free(file->end_heredoc);
	return (NULL);
}
