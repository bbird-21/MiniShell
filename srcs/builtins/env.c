/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:33:29 by alvina            #+#    #+#             */
/*   Updated: 2023/03/21 14:12:33 by ale-sain         ###   ########.fr       */
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
    exit(0);
}