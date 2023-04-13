/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:33:39 by alvina            #+#    #+#             */
/*   Updated: 2023/04/13 16:44:03 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(char **arg)
{
	char	*key;

	key = arg[0];
	if (!check_arg(arg, 1, "unset"))
	{
		g_g.exit_status = 1;
		return ;
	}
	g_g.exit_status = 0;
	if (!key)
		return ;
	handler(1, NULL, key);
	g_g.exit_status = 0;
}
