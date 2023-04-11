/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 21:14:27 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/04/11 21:32:51 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	extra_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
		{
			while (tab[i] && tab[i][0])
			{
				free(tab[i]);
				i++;
				if (tab[i] && !tab[i][0])
				{
					free(tab[i]);
					i++;
				}	
			}
			if (tab[i] && !tab[i][0])
				free(tab[i]);
		}
}