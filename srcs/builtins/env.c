/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:33:29 by alvina            #+#    #+#             */
/*   Updated: 2023/04/11 20:37:49 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char **arg)
{
	t_list	*envp;

	(void)arg;
	if (!check_arg(arg, 0, "env"))
	{
		g.exit_status = 1;
		handler(CLEANING, NULL, NULL);
		mini_gc(NULL, NULL);
		exit(1);
	}
	envp = handler(5, NULL, NULL);
	if (envp)
		print_lst(envp, print_env);
	handler(CLEANING, NULL, NULL);
	mini_gc(NULL, NULL);
	rl_clear_history();
	exit(0);
}
