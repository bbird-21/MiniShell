/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< Updated upstream
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:49:16 by ale-sain          #+#    #+#             */
/*   Updated: 2023/04/24 16:48:43 by ale-sain         ###   ########.fr       */
=======
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:49:16 by ale-sain          #+#    #+#             */
/*   Updated: 2023/04/24 16:25:42 by mmeguedm         ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_globale	g_g = {0};

static void	handle_signal(void)
{
	ft_state(READLINE);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &sig_handler);
	signal(SIGTSTP, SIG_IGN);
}

int	main(int ac, char **av, char **env)
{
	char		*str;

	if (!isatty(0))
		return (-1);
	(void)ac;
	(void)av;
	(void)env;
	handler(0, env, NULL);
	rl_outstream = stderr;
	while (21)
	{
		handle_signal();
		str = readline("femtoshell > ");
		if (!str)
		{
			ft_putstr_fd("exit\n", 2);
			handler(CLEANING, NULL, NULL);
			exit(g_g.exit_status);
		}
		if (!str[0] || only_wspace(str))
			continue ;
		add_history(str);
		first_split(str);
	}
}
