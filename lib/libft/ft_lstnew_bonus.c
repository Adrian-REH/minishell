/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 00:39:42 by adherrer          #+#    #+#             */
/*   Updated: 2024/09/15 06:31:30 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*val;

	val = (t_list *)malloc(sizeof(t_list));
	if (!val)
		return (0);
	val->content = content;
	val->next = 0;
	return (val);
}
