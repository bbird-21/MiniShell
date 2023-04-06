/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:06:34 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/04/06 15:23:58 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	sig_int(int state)
{
	int fd;

	// if (state == 4)
	// 	printf("\n");
	if (state == READLINE)
	{
		ft_putstr_fd("\n", 2);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 130;
	}
	else if (state == PIPEX)
	{
		ft_putstr_fd("\n", 2);
		g_exit_status = 130;
	}
	else if (state == HERE_DOC)
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
		ft_putstr_fd("Quit (core dumped)\n", 2);
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
