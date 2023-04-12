/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:45:35 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/04/12 19:09:20 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(int sig_err)
{
	const char	*map_error[ERR__LENGHT] = {
		"Error while opening file\n",
		"Invalid number of arguments\n",
		"No such file or directory\n",
		"Command not found\n",
		"An error occurred while executing fork\n",
		"An error occurred while executing pipe\n",
		"Memory error\n",
		"No environnement has been detected. Did you try to kill me ?\n",
		"Path has been dectivate. Did you try to kill me ?\n"};

	ft_putstr_fd((char *)map_error[sig_err], STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	signal_check(int status, int i, int last_cmd)
{
	if (status == -21)
	{
		mini_gc(NULL, NULL);
		exit_malloc();
	}
	else if (status == 2 && i == last_cmd)
	{
		g.exit_status = 130;
		ft_putstr_fd("\n", 2);
	}
	else if (status == 131 && i == last_cmd)
	{
		g.exit_status = 131;
		ft_putstr_fd("Quit (core dumped) zebbbbi\n", 2);
	}
	else if (WTERMSIG(status) == 11)
	{
		ft_putstr_fd("Segmentation fault (core dumped)\n", STDERR_FILENO);
		g.exit_status = 139;
	}
}

void	builtin_no_child(t_storage_cmd *st_cmd)
{
	execve_builtin(is_builtin(st_cmd->bin_args[0], 0), st_cmd->bin_args);
	if (g.exit_malloc)
	{
		mini_gc(NULL, NULL);
		exit_malloc();
	}
	return (mini_gc(NULL, NULL));
}
