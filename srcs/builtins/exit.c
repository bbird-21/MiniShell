/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:11:19 by ale-sain          #+#    #+#             */
/*   Updated: 2023/03/21 13:43:42 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "minishell.h"

static unsigned long long	ft_atoll(const char *nptr)
{
	int		i;
	unsigned long long nb;
	int		neg;

	i = 0;
	nb = 0;
	neg = 1;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg = -1;
		i++;
	}
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - 48);
		i++;
        if ((nb > (unsigned long long)LLONG_MAX && neg == 1) ||
            (neg == -1 && (-nb) < (unsigned long long)LLONG_MIN))
            return (0);
	}
    if (nptr[i])
        return (0);
    else
	    return (nb * neg);
}

void    ft_exit(char **arg)
{
    long long n;
    char    *str;
    
    if (!check_arg(arg, 1, "exit"))
    {
        g_exit_status = 1;
        exit(1);
    }
    if (*arg)
        str = arg[0];
    else
        str = NULL;
    if (!str || (ft_strlen(str) == 1 && str[0] == '0'))
    {
        g_exit_status = 0;
        ft_putstr_fd("exit\n", 2);
        exit(0);
    }
    n = ft_atoll(str);
    if (!n)
    {
        g_exit_status = 2;
        ft_putstr_fd("nanoshell: exit: ", 2);
        ft_putstr_fd(str, 2);
        ft_putendl_fd(": numeric argument required", 2);
        exit(2);
    }
    ft_putstr_fd("exit\n", 2);
    if (n >= 0 && n <= 255)
    {
        g_exit_status = n;
        exit(n);
    }
    if (n <= -1 && n >= -255)
    {
        g_exit_status =  256 + n;
        exit(256 + n);
    }
    if (n > 255 || n < -255)
    {
        if (n < 0)
            n = -n;
        g_exit_status = n % 256;
        exit(n % 256);
    } 
}
