/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 22:36:29 by adherrer          #+#    #+#             */
/*   Updated: 2024/07/13 22:21:19 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*src;
	size_t	i;

	i = 0;
	src = ft_calloc(ft_strlen(s1) + 1, sizeof(char));
	if (!src)
		return (0);
	while (*s1)
		src[i++] = *s1++;
	src[i] = 0;
	return (src);
}
/* int main() {
    // Test case
    char *s1 = "Hello, world!";
    char *result = ft_strdup(s1);
    write(1, "Test case:\n", 11);
    write(1, "Source string: \"", 16);
    write(1, s1, strlen(s1));
    write(1, "\"\n", 2);
    write(1, "Duplicated string: \"", 20);
    write(1, result, strlen(result));
    write(1, "\"\n", 2);
    write(1, "Expected result: \"Hello, world!\"\n", 29);

    if (strcmp(result, "Hello, world!") == 0) {
        write(1, "Test passed.\n", 13);
    } else {
        write(1, "Test failed.\n", 13);
    }

    free(result);

    return 0;
} */