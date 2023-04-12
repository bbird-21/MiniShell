/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:55:39 by ale-sain          #+#    #+#             */
/*   Updated: 2023/04/11 20:19:39 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define NO_ENDL 0
#define ENDL 1

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

static void	ft_putnbr_fd(int n, int fd)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nb = -nb;
	}
	if (nb > 9)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(nb % 10, fd);
	}
	else
		ft_putchar_fd(nb + 48, fd);
}

static void	print_tab(char **tab, int i, int j)
{
	if (!*tab)
		return ;
	while (tab[i])
	{
		while (tab[i][j])
		{
			if (!ft_strncmp(&tab[i][j], "$?", 2))
			{
				ft_putnbr_fd(g.exit_status, 1);
				j += 2;
			}
			else
			{
				write(1, &tab[i][j], 1);
				j++;
			}
		}
		if (tab[i + 1])
			write(1, " ", 1);
		j = 0;
		i++;
	}
}

void	result_echo(int n, int to_print, char **arg)
{
	if (n == NO_ENDL)
	{
		if (to_print)
			print_tab(&arg[to_print], 0, 0);
	}
	else
	{
		if (arg)
			print_tab(arg, 0, 0);
		write(1, "\n", 1);
	}
	mini_gc(NULL, NULL);
	handler(CLEANING, NULL, NULL);
	rl_clear_history();
	exit(0);
}

void	echo(char **arg)
{
	int	i;
	int	n;
	int	to_print;

	i = 0;
	n = ENDL;
	to_print = 0;
	rl_clear_history();
	if (!arg || !*arg)
	{
		write(1, "\n", 1);
		handler(CLEANING, NULL, NULL);
		return (rl_clear_history(), mini_gc(NULL, NULL), exit(0));
	}
	while (arg[i])
	{
		if (!slash_n(arg[i]))
		{
			to_print = i;
			break ;
		}
		n = NO_ENDL;
		i++;
	}
	result_echo(n, to_print, arg);
}
