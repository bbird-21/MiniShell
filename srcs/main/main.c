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

void	sig_handler(int signum)
{
	int state;

	state = ft_state(-1);
	if (signum == 2)
	{
		if (state == 0)
		{
			ft_putstr_fd("\n", 2);
			rl_on_new_line();
			rl_redisplay();
			g_exit_status = 130;
		}
		else if (state == 1)
		{
			ft_putstr_fd("\n", 2);
			g_exit_status = 130;
		}
		else
			exit(130);
	}
	else
	{
		if (state == 1)
		{
			ft_putstr_fd("Quit (core dumped zebi)\n", 2);
			g_exit_status = 131;
		}
		else
			exit(131);
	}
}

int	ft_state(int state)
{
	static int pos;

	if (state >= 0)
		pos = state;
	return (pos);
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
		ft_state(0);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &sig_handler);
        str = readline("femtoshell > ");
		if (!str)
		{
			ft_putstr_fd("exit\n", 2);
			mini_gc(NULL, NULL);
			handler(DELETING, NULL, NULL);
			exit(0);
		}
		first_split(str);
	}
}
