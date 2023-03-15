/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 00:49:24 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/02/22 16:24:46 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_dblist(void (*fp)(t_dblist *), t_dblist **dblist)
{
	static	t_dblist	st_dblist;
	
	if (fp)
		fp(&st_dblist);
	(*dblist) = &st_dblist;
}

// int	a = 21;
// int	*b;

// b = addr;
// a = value;
// int	function(int *a)
// {

// }
