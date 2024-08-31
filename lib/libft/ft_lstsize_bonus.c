/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 01:19:36 by adherrer          #+#    #+#             */
/*   Updated: 2024/07/13 22:21:19 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst -> next;
		i++;
	}
	return (i);
}
/* 
int	main() {

	// Creación de algunos nodos
	t_list	*node1 = (t_list *)malloc(sizeof(t_list));
	t_list	*node2 = (t_list *)malloc(sizeof(t_list));

	// Asignación de contenido a los nodos
	node1->content = "Primero";
	node1->next = 0;
	node2->content = "Segundo";
	node2->next = node1;

	// Agregar nodos a la lista
	printf("%d",ft_lstsize(node2));


	// Liberar la memoria asignada a los nodos
	free(node1);
	free(node2);

	return (0);
} */