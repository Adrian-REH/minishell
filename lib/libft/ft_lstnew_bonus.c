/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 00:39:42 by adherrer          #+#    #+#             */
/*   Updated: 2024/07/13 22:21:19 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*val;

	val = (t_list *)malloc(sizeof(t_list));
	if (!val)
		return (0);
	val -> content = content;
	val -> next = 0;
	return (val);
}
/* 
int	main() {

	// Creación de algunos nodos
	t_list	*gst = ft_lstnew("Algunas cosas");

	printf("%s", gst->content);
	return (0);
}  */