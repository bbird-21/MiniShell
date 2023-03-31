/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:10:40 by alvina            #+#    #+#             */
/*   Updated: 2023/03/31 13:15:33 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <linux/limits.h>

void	pwd(char **arg)
{
	char	*pwd;

	if (!check_arg(arg, 0, "pwd"))
	{
		g.exit_status = 1;
		handler(CLEANING, NULL, NULL);
		mini_gc(NULL, NULL);
		exit(1);
	}
	(void)arg;
	pwd = malloc(sizeof(char) * PATH_MAX);
	getcwd(pwd, PATH_MAX);
	ft_putendl_fd(pwd, 1);
	g.exit_status = 0;
	free(pwd);
	mini_gc(NULL, NULL);
	rl_clear_history();
	handler(CLEANING, NULL, NULL);
	exit(0);
}
