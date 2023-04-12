/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 21:14:27 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/04/12 18:02:47 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	extra_free_tab(char ***tab)
{
	int	i;

	i = 0;
	if (*tab)
	{
		while ((*tab)[i] && (*tab)[i][0])
		{
			free((*tab)[i]);
			i++;
			if ((*tab)[i] && !(*tab)[i][0])
			{
				free((*tab)[i]);
				i++;
			}
		}
		if ((*tab)[i] && !(*tab)[i][0])
			free((*tab)[i]);
	}
}

void	extra_creating_new(char ***new, char **expand_var, int *j, int *k)
{
	while ((*expand_var)[*j])
		(**new)[(*k)++] = (*expand_var)[(*j)++];
	free(*expand_var);
	*expand_var = NULL;
}
