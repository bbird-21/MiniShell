/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:33:29 by alvina            #+#    #+#             */
/*   Updated: 2023/03/24 11:19:41 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_env(char **arg)
{
    t_list   *envp;

    (void)arg;
    if (!check_arg(arg, 0, "env"))
    {
        g_exit_status = 1;
        exit(1);
    }
    envp = handler(5, NULL, NULL);
    if (envp)
        print_lst(envp, print_env);
    handler(CLEANING, NULL, NULL);
    mini_gc(NULL, NULL);
    exit(0);
}