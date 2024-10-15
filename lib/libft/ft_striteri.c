/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 00:07:07 by adherrer          #+#    #+#             */
/*   Updated: 2024/07/13 22:21:19 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/* void print_index_char(unsigned int index, char *chr) {
    char index_char[20];
    char char_buf[2] = {*chr, '\0'};
    size_t i = 0;

    // Convertir el índice a una cadena
    while (index > 0) {
        index_char[i++] = (index % 10) + '0';
        index /= 10;
    }
    if (i == 0)
        index_char[i++] = '0';
    index_char[i] = '\0';

    // Escribir el índice y el carácter en la salida estándar
    write(1, "Index: ", 7);
    write(1, index_char, i);
    write(1, ", Character: ", 13);
    write(1, char_buf, 1);
    write(1, "\n", 1);
}

int main() {
    // Test case
    char s[] = "Hello";
    write(1, "Test case:\n", 11);
    write(1, "Original string: \"Hello\"\n", 25);
    write(1, "Applying function ft_striteri:\n", 32);
    ft_striteri(s, &print_index_char);

    return 0;
} */