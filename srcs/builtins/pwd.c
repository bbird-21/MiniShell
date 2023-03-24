/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:10:40 by alvina            #+#    #+#             */
/*   Updated: 2023/03/24 11:19:46 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

void    pwd(char **arg)
{
    char    *pwd;
    
    (void)arg;
    pwd = malloc(sizeof(char) * PATH_MAX);
    getcwd(pwd, PATH_MAX);
    ft_putendl_fd(pwd, 1);
    g_exit_status = 0;
    free(pwd);
    mini_gc(NULL, NULL);
    handler(CLEANING, NULL, NULL);
    exit(0);
}