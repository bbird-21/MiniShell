/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:10:40 by alvina            #+#    #+#             */
/*   Updated: 2023/04/11 20:49:40 by mmeguedm         ###   ########.fr       */
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
		return (mini_gc(NULL, NULL), handler(CLEANING, NULL, NULL), exit(1));
	}
	(void)arg;
	pwd = malloc(sizeof(char) * PATH_MAX);
	if (!pwd)
	{
		mini_gc(NULL, NULL);
		rl_clear_history();
		handler(CLEANING, NULL, NULL);
		exit(-21);
	}
	if (!getcwd(pwd, PATH_MAX))
		perror("getcwd");
	ft_putendl_fd(pwd, 1);
	g.exit_status = 0;
	free(pwd);
	mini_gc(NULL, NULL);
	handler(CLEANING, NULL, NULL);
	exit(0);
}
