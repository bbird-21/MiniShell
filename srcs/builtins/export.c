/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:03:03 by alvina            #+#    #+#             */
/*   Updated: 2023/03/21 13:46:17 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_correct(char *str)
{
    int i;

    i = 0;
    if (!ft_isalpha(str[0]) && str[0] != '_')
        return (0);
    while (str[i] && str[i] != '=')
    {
        if (str[i] == '+' && str[i + 1] == '=')
            break;
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (0);
        i++;
    }
	return (1);
}

void   export(char **arg)
{
    t_list  *envp;
    char    *key;
    char    *var;
    char    *name;
    
    if (!check_arg(arg, 1, "export"))
    {
        g_exit_status = 1;
        return ;
    }
    name = arg[0];
    envp = handler(5, NULL, NULL);
    g_exit_status = 0;
    if (!name)
        return (print_lst(envp, print_env));
    if (!ft_strchr(name, '='))
        return ;
    if (!is_correct(name) || (ft_strlen(name) == 1 && name[0] == 0))
    {
        g_exit_status = 1;
        ft_putendl_fd("export : not a valid identifier", 2);
        return ;
    }
    key = ft_key(name);
    var = ft_getenv(key);
    if (var)
    {
        free(var);
        if (ft_strnstr(name, "+=", ft_strlen(name)))
            handler(6, NULL, name);
        else
            handler(3, NULL, name);
    }
    else
        handler(2, NULL, name);
    free(key);
    g_exit_status = 0;
    return ;
}