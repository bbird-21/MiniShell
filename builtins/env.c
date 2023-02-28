/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:33:29 by alvina            #+#    #+#             */
/*   Updated: 2023/02/28 19:08:57 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
extern int	g_exit_status;

void    ft_env(void)
{
    t_list   *envp;

    envp = handler(5, NULL, NULL);
    g_exit_status = 0;
    print_lst(envp, print_env);
}