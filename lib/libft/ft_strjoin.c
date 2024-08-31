/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:47:55 by adherrer          #+#    #+#             */
/*   Updated: 2024/07/13 22:21:19 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;

	dst = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!dst)
		return (0);
	ft_strlcpy(dst, s1, ft_strlen(s2) + ft_strlen(s1) + 1);
	ft_strlcat(dst, s2, ft_strlen(s2) + ft_strlen(s1) + 1);
	return (dst);
}
/* int main() {
    // Test case
    char *s1 = "Hello, ";
    char *s2 = "world!";
    char *result = ft_strjoin(s1, s2);
    write(1, "Test case:\n", 11);
    write(1, "String 1: \"", 11);
    write(1, s1, strlen(s1));
    write(1, "\"\n", 2);
    write(1, "String 2: \"", 11);
    write(1, s2, strlen(s2));
    write(1, "\"\n", 2);
    write(1, "Result string: \"", 16);
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