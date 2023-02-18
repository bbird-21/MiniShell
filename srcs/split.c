/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 09:55:05 by alvina            #+#    #+#             */
/*   Updated: 2023/02/18 19:13:43 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	length(char *str, int *state)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (*state == 0 && is_separator(&str[i]))
			return (i);
		i++;
		*state = changing_state(str[i], *state);
	}
	return (i);
}

int    wording_sep(char *str, char ***tab, int j, int (*f)(char *))
{
    int i;

    i = 0;
    (*tab)[j] = malloc(sizeof(char) * (f(str) + 1));
    if (!(*tab)[j])
	{
		free_tab(*tab, j), 0;
		exit(0);
	}
	while (f(&str[i]) && str[i])
	{
		(*tab)[j][i] = str[i];
		i++;
	}
	(*tab)[j][i] = '\0';
	return (i);
}

int		wording_other(char *str, char ***tab, int j, int *state)
{
	int	i;
	int	len;

	i = 0;
	len = length(str, state);
	(*tab)[j] = malloc(sizeof(char) * len + 1);
	if (!(*tab)[j])
	{
		free_tab(*tab, j), 0;
		exit(0);
	}
	while (i < len)
	{
		(*tab)[j][i] = str[i];
		i++;
	}
	(*tab)[j][i] = '\0';
	return (i);
}

char	**splitting(char **tab, char *str, int state)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (str[i])
	{
        state = changing_state(str[i], state);
        if (state == 0 && is_separator(&str[i]))
        {
            if (!is_space(&str[i]))
            {
                if (is_pipe(&str[i]))
                    i += wording_sep(&str[i], &tab, j, is_pipe);
				else
                    i += wording_sep(&str[i], &tab, j, is_red);
			    j++;
            }
			else
				i++;
        }
		else if (str[i] != ' ' || state != 0)
		{
			i += wording_other(&str[i], &tab, j, &state);
			j++;
		}
		else
			i++;
	}
	tab[j] = 0;
	return (tab);
}

char	**first_split(char *str)
{
	char	**tab;
    int     state;

    state = 0;
	if (!str || str[0] == 0)
		return (NULL);
	if (count_words(str) == 0)
		return (NULL);
	tab = (char **) malloc(sizeof(char *) * (count_words(str) + 1));
	if (!tab)
		return (NULL);
	return (splitting(tab, str, state));
}