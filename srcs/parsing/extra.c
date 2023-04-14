/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 21:14:27 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/04/14 23:43:28 by mmeguedm         ###   ########.fr       */
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

static int	is_wspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	only_wspace(char *str)
{
	while (*str)
	{
		if (!is_wspace(*str))
			return (0);
		str++;
	}
	return (1);
}
