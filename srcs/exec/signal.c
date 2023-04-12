/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:06:34 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/04/12 16:54:04 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int(int state)
{
	int	fd;

	if (state == READLINE)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g.exit_status = 130;
	}
	else if (state == PIPEX)
		g.exit_status = 130;
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
		g.exit_status = 131;
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
