/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_structs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 06:10:57 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/23 01:31:46 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/headers/minishell.h"

void	ft_print_file(t_file *f)
{
	printf("\t\tinput:        %d\n", f->input);
	printf("\t\toutput:       %d\n", f->output);
	printf("\t\tfd_aux[0]:    %d | fd_aux[1]: %d\n", \
	f->fd_aux[0], f->fd_aux[1]);
	printf("\t\tlen_content:  %d\n", f->len_content);
	printf("\t\tidfile:       %s\n", f->idfile);
	printf("\t\todfile:       %s\n", f->odfile);
	printf("\t\tend_heredoc:  %s\n", f->end_heredoc);
}
