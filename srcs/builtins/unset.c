/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:33:39 by alvina            #+#    #+#             */
/*   Updated: 2023/03/15 19:06:05 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void    unset(char **arg)
{
    char    *key;

    key = arg[0];
    g_exit_status = 0;
    if (!key)
        return ;
    if (!is_correc(key))
    {
        // ft_putstr_fd("unset: ", 2);
        // ft_putstr_fd(key, 2);
        // ft_putendl_fd(": invalid parameter name", 2);
        return ;
    }
    handler(1, NULL, key);
}