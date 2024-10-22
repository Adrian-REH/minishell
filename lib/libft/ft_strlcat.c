/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:22:14 by adherrer          #+#    #+#             */
/*   Updated: 2024/07/13 22:21:19 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	n;
	size_t	size_src;
	size_t	size_dest;

	n = -1;
	size_src = ft_strlen(src);
	size_dest = ft_strlen(dst);
	if (dstsize < size_dest + 1)
		return (size_src + dstsize);
	while (++n < (dstsize - size_dest - 1) && *src)
		*(dst + size_dest + n) = *src++;
	*(dst + size_dest + n) = 0;
	return (size_dest + size_src);
}
/* int main() {
    // Test case: dstsize es mayor o igual que el tamaño de src
    char src[] = "Hello";
    char dst[10] = "world";
    size_t result = ft_strlcat(dst, src, sizeof(dst));
    write(1, "Test case:\n", 11);
    write(1, "Source string: \"", 16);
    write(1, src, strlen(src));
    write(1, "\"\n", 2);
    write(1, "Destination string: \"", 21);
    write(1, dst, strlen(dst));
    write(1, "\"\n", 2);
    write(1, "Return value: ", 14);
    char ret_str[20];
    sprintf(ret_str, "%zu", result);
    write(1, ret_str, strlen(ret_str));
    write(1, "\n", 1);
    write(1, "Expected result: 10\n", 20);

    if (result == 10 && ft_strcmp(dst, "worldHello") == 0) {
        write(1, "Test passed.\n", 13);
    } else {
        write(1, "Test failed.\n", 13);
    }

    return 0;
} */