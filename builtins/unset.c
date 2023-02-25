/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:33:39 by alvina            #+#    #+#             */
/*   Updated: 2023/02/24 19:13:16 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int is_correc(char *str)
{
    int i;

    i = 0;
    if (!ft_isalpha(str[0]) && str[0] != '_')
        return (0);
    while (str[i])
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (0);
        i++;
    }
	return (1);
}

void    unset(char *key)
{
    if (!key)
    {
        ft_putendl_fd("unset : not enough arguments", 2);
        return ;
    }
    if (!is_correc(key))
    {
        ft_putstr_fd("unset: ", 2);
        ft_putstr_fd(key, 2);
        ft_putendl_fd(": invalid parameter name", 2);
        return ;
    }
    handler(1, NULL, key);
}