/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_open_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 01:50:23 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/23 01:50:33 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/headers/minishell.h"

int	is_fd_open(int fd)
{
	struct stat	statbuf;

	return ((fstat(fd, &statbuf) != -1 || errno != EBADF) && fd > 2);
}
