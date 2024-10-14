/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:17:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/07/13 22:21:19 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
		if (*s++ == (char)c)
			return ((char *)(s - 1));
	if (*s == (char)c)
		return ((char *)s);
	return (0);
}
/* write_str(const char *str) {
    write(1, str, strlen(str));
}

void write_char(char c) {
    write(1, &c, 1);
}

void write_int(int n) {
    if (n == 0) {
        write_char('0');
        return;
    }

    int rev = 0;
    while (n != 0) {
        rev = rev * 10 + n % 10;
        n /= 10;
    }

    while (rev != 0) {
        write_char(rev % 10 + '0');
        rev /= 10;
    }
}

int main() {
    // Test case 1: Character exists in string
    char *s = "Hello, world!";
    int c = 'w';
    char *result = ft_strchr(s, c);
    write_str("Test case 1:\n");
    write_str("Source string: \"");
    write_str(s);
    write_str("\"\n");
    write_str("Character to find: '");
    write_char(c);
    write_str("'\n");
    write_str("Result: ");
    if (result != NULL) {
        write_str("Found character at position ");
        write_int(result - s);
        write_char('\n');
    } else {
        write_str("Character not found\n");
    }

    // Test case 2: Character doesn't exist in string
    c = 'z';
    result = ft_strchr(s, c);
    write_str("\nTest case 2:\n");
    write_str("Source string: \"");
    write_str(s);
    write_str("\"\n");
    write_str("Character to find: '");
    write_char(c);
    write_str("'\n");
    write_str("Result: ");
    if (result != NULL) {
        write_str("Found character at position ");
        write_int(result - s);
        write_char('\n');
    } else {
        write_str("Character not found\n");
    }

    return 0;
}
 */