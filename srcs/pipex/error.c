/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:45:35 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/30 14:06:25 by ale-sain         ###   ########.fr       */
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
