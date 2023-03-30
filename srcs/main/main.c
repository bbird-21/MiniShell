/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:49:16 by ale-sain          #+#    #+#             */
/*   Updated: 2023/03/30 15:24:29 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

int		g_exit_status;

int	get_nb_cmd(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	sig_int(int state)
{
	int fd;

	if (state == 4)
	{
		printf("\n");
		return ;
	}
	if (state == 0)
	{
		ft_putstr_fd("\n", 2);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 130;
	}
	else if (state == 1)
	{
		printf("state = 1\n");
		ft_putstr_fd("\n", 2);
		g_exit_status = 130;
	}
	else if (state == 3)
	{
		fd = open("/dev/null", O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else
		exit(130);
}

void	sig_quit(int state)
{
	if (state == 1)
	{
		ft_putstr_fd("Quit (core dumped zebi)\n", 2);
		g_exit_status = 131;
	}
	else
		exit(131);
}

void	sig_handler(int signum)
{
	int	state;

	state = ft_state(-1);
	if (signum == 2)
		sig_int(state);
	else
		sig_quit(state);
}

int	ft_state(int state)
{
	static int	pos;

	if (state >= 0)
		pos = state;
	return (pos);
}

int	main(int ac, char **av, char **env)
{
	char	*str;

	(void)ac;
	(void)av;
	(void)env;
	g_exit_status = 0;
	handler(0, env, NULL);
	rl_outstream = stderr;
	ft_state(4);
	while (21)
	{
		ft_state(0);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &sig_handler);
		str = readline("femtoshell > ");
		printf("\r");
		if (!str)
		{
			ft_putstr_fd("exit\n", 2);
			handler(CLEANING, NULL, NULL);
			exit(0);
		}
		first_split(str);
	}
}
