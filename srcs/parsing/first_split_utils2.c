/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_split_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:46:22 by alvina            #+#    #+#             */
/*   Updated: 2023/03/30 11:36:02 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	changing_state(char c)
{
	static int	state;

	if (c == (char)-1)
		state = 0;
	if (c == (char)-2)
		return (state);
	else if (c == 39)
	{
		if (state == 1)
			state = 0;
		else if (state == 0)
			state = 1;
	}
	else if (c == '"')
	{
		if (state == 2)
			state = 0;
		else if (state == 0)
			state = 2;
	}
	return (state);
}

int	length(char *str)
{
	int	i;
	int	state;

	i = 0;
	if (!str)
		return (0);
	state = changing_state((char)-2);
	while (str[i])
	{
		if (state == 0 && is_separator(&str[i]))
			return (i);
		i++;
		state = changing_state(str[i]);
	}
	return (i);
}
