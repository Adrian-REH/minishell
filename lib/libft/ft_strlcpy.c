/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 19:53:59 by adherrer          #+#    #+#             */
/*   Updated: 2024/07/13 22:21:19 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	srcsize;

	i = 0;
	srcsize = ft_strlen(src);
	while ((i + 1) < dstsize && dstsize && *src)
		dst[i++] = *src++;
	if (dstsize > 0)
		dst[i] = 0;
	return (srcsize);
}
/* int main() {
    // Test case: dstsize es mayor o igual que el tamaño de src
    char src[] = "Hello, world!";
    char dst[20];
    size_t result = ft_strlcpy(dst, src, sizeof(dst));
    write(1, "Test case:\n", 11);
    write(1, "Source string: \"", 16);
    write(1, src, strlen(src));
    write(1, "\"\n", 2);
    write(1, "Copied string: \"", 16);
    write(1, dst, strlen(dst));
    write(1, "\"\n", 2);
    write(1, "Return value: ", 14);
    char ret_str[20];
    sprintf(ret_str, "%zu", result);
    write(1, ret_str, strlen(ret_str));
    write(1, "\n", 1);
    write(1, "Expected result: ", 17);
    char exp_str[20];
    sprintf(exp_str, "%zu", strlen(src));
    write(1, exp_str, strlen(exp_str));
    write(1, "\n", 1);

    if (result == strlen(src) && strcmp(dst, src) == 0) {
        write(1, "Test passed.\n", 13);
    } else {
        write(1, "Test failed.\n", 13);
    }

    return 0;
} */