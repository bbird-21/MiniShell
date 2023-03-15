/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:55:39 by ale-sain          #+#    #+#             */
/*   Updated: 2023/03/15 19:11:19 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

# define NO_ENDL 0
# define ENDL 1

static int	slash_n(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (0);
	if (str[i])
	{
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;	
		}
		return (1);
	}
	return (0);
}

static void	print_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		ft_putstr_fd(tab[i], 1);
		if (tab[i + 1])
			write(1, " ", 1);
		i++;
	}
}

void	echo(char **arg)
{
	int	i;
	int n;
	int	to_print;

	i = 0;
	n = ENDL;
	to_print = 0;
	if (!arg || !*arg)
	{
		write(1, "\n", 1);
		return ;
	}
	while (arg[i])
	{
		if (!slash_n(arg[i]))
		{
			to_print = i;
			break;
		}
		n = NO_ENDL;
		i++;
	}
	if (n == NO_ENDL && to_print != 0)
		print_tab(&arg[to_print]);
	else
	{
		if (arg)
			print_tab(arg);
		write(1, "\n", 1);
	}
	g_exit_status = 0;
}