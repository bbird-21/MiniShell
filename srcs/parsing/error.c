/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 00:16:17 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/04/06 20:29:58 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exit(char *error)
{
	perror(error);
	clear_history();
	exit(g_exit_status);
}

int	error_msg(char *value)
{
	ft_putstr_fd("nanoshell: syntax error near unexpected token : ", 2);
	ft_putendl_fd(value, 2);
	g_exit_status = 2;
	return (0);
}
