/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 01:27:56 by adherrer          #+#    #+#             */
/*   Updated: 2024/07/13 22:21:19 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*prv;

	prv = 0;
	while (lst)
	{
		prv = lst;
		lst = lst -> next;
	}
	return (prv);
}
/* 
int	main() {

	// Creación de algunos nodos
	t_list	*node1 = (t_list *)malloc(sizeof(t_list));
	t_list	*node2 = (t_list *)malloc(sizeof(t_list));
	t_list	*node0 = (t_list *)malloc(sizeof(t_list));

	// Asignación de contenido a los nodos
	node2->content = "Segundo";
	node2->next = 0;
	node1->content = "Primero";
	node1->next = node2;
	node0->content = "Cero";
	node0->next = node1;

	// Agregar nodos a la lista
	printf("Expect: Segundo - Result: %s",(char *)ft_lstlast(node0)->content);


	// Liberar la memoria asignada a los nodos
	free(node1);
	free(node2);
	free(node0);

	return (0);
} */