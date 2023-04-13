/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 21:14:27 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/04/13 15:40:09 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	extra_free_tab(char ***tab)
{
	int	i;

	i = 0;
	if (*tab)
	{
		while (*(tab) && (*tab)[i])
		{
			free((*tab)[i]);
			i++;
		}
	}
}

void	extra_creating_new(char ***new, char **expand_var, int *j, int *k)
{
	while ((*expand_var)[*j])
		(**new)[(*k)++] = (*expand_var)[(*j)++];
	free(*expand_var);
	*expand_var = NULL;
}
