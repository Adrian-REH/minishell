/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-clee <jde-clee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 01:36:36 by jde-clee          #+#    #+#             */
/*   Updated: 2024/07/11 17:09:43 by jde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/headers/minishell.h"
void ft_free_matrix(char **str, size_t j)
{
    while (j-- > 0)
        free(str[j]);
    free(str);
}
/*
CUENTA LA CANTIDAD DE BYTES A ALMACENAR EN LA DIMENSION DE MÁS AFUERA
-LA CANTIDAD DE STRINGS SEPARADAS, BÁSICAMENTE-
*/

size_t ft_n_strings(char *s, char c)
{
    size_t i;
    size_t n_strings;

    i = 0;
    n_strings = 0;
    while (s && s[i])
    {
        if (s[i] != c)
        {
            n_strings++;
            while (s[i] != c && s[i])
                i++;
        }
        else
            i++;
    }
    return (n_strings);
}

size_t ft_n_chars(char *s, char c, size_t i)
{
    size_t size;

    size = 0;
    while (s[i] != c && s[i])
    {
        i++;
        size++;
    }
    return (size);
}

char **ft_split(char *s, char c)
{
    size_t i;
    size_t j;
    char **final_s;

    i = 0;
    j = -1;
    final_s = malloc(sizeof(char *) * (ft_n_strings(s, c) + 1));
    if (!(final_s))
        return (NULL);
    while (++j < ft_n_strings(s, c))
    {
        while (s[i] == c)
            i++;
        ft_n_chars(s, c, i);
        final_s[j] = ft_substr(s, i, ft_n_chars(s, c, i));
        if (!(final_s[j]))
            return (ft_free_matrix(final_s, j), NULL);
        i = i + ft_n_chars(s, c, i);
    }
    free(s);
    return (final_s[j] = 0, final_s);
}
