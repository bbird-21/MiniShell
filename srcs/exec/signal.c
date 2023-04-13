/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:06:34 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/04/13 14:19:15 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	sig_int(int state)
{
	int fd;

	g_g.exit_status = 130;
	if (state == READLINE)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (state == PIPEX)
		g_g.exit_status = 130;
	else if (state == HERE_DOC)
	{
		fd = open("/dev/null", O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);	
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_g.exit_here_doc = 1;
	}
	else
		exit(130);
}

void	sig_quit(int state)
{
	if (state == 1)
		g_g.exit_status = 131;
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
