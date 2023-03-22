/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:49:16 by ale-sain          #+#    #+#             */
/*   Updated: 2023/03/22 17:22:26 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

int	g_exit_status;

void	main_doko(int signum)
{
	if (signum == 2)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_redisplay();
    	g_exit_status = 130;
	}
	else if (signum == 3)
		g_exit_status = 131;
}

void	heredoc_doko(int signum)
{
	if (signum == 2)
		g_exit_status = -1;
	else if (signum == 3)
		g_exit_status = -2;
}

// void	exec_doko(int signum)
// {
	
// }

void	catch_signals(int dokoro)
{
	struct sigaction	sa_c;

	if (!dokoro)
		sa_c.sa_handler = main_doko;
	else if (dokoro == 1)
		sa_c.sa_handler = heredoc_doko;
	// else
	// 	sa_c.sa_handler = exec_doko;
	sigaction(SIGINT, &sa_c, NULL);
	sigaction(SIGQUIT, &sa_c, NULL);
}

int main(int ac, char **av, char **env)
{
	char	*str;
	
	(void)ac;
	(void)av;
	(void)env;
	g_exit_status = 0;
	handler(0, env, NULL);
	rl_outstream = stderr;
	while (21)
	{
		catch_signals(0);
        str = readline("femtoshell > ");
		if (!str)
		{
			ft_putstr_fd("exit\n", 2);
			exit(0);
		}
		first_split(str);
	}
}
