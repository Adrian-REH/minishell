/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 01:33:26 by adherrer          #+#    #+#             */
/*   Updated: 2024/07/13 22:21:19 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = ft_lstlast(*(lst));
	tmp->next = new;
}
/* 

int main() {
    // Inicialización de la lista como vacía
    t_list *list = NULL;

    // Creación de algunos nodos
    t_list *node1 = (t_list *)malloc(sizeof(t_list));
    t_list *node2 = (t_list *)malloc(sizeof(t_list));

    // Asignación de contenido a los nodos
    node1->content = "Primero";
    node2->content = "Segundo";

    // Asegurarnos de que los siguientes apunten a NULL
    node1->next = NULL;
    node2->next = NULL;

    // Agregar nodos a la lista
    ft_lstadd_back(&list, node1);
    ft_lstadd_back(&list, node2);

    // Imprimir la lista resultante
    print_list(list);

    // Liberar la memoria asignada a los nodos
    free(node1);
    free(node2);

    return 0;
} */