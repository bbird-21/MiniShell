/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:29:39 by alvina            #+#    #+#             */
/*   Updated: 2023/04/21 01:01:39 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(char *str)
{
	char	*new;
	char	state_char;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * ft_strlen(str) - 1);
	if (!new)
	{
		g_g.exit_malloc = 1;
		exit(12);
	}
	state_char = str[i];
	str++;
	while (str[i] && str[i] != state_char)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = 0;
	return (new);
}

int	get_var_size(char *str)
{
	int	i;
	int	vr_size;

	vr_size = 0;
	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		i++;
		vr_size++;
	}
	return (vr_size);
}

void	magic_space(char *str)
{
	if (!str)
		return ;
	while (*str)
	{
		if (*str == SPACE)
			*str *= -1;
		str++;
	}
}

char	*expansion(char *token)
{
	char	*new;

	new = malloc(sizeof(char) * (get_exp_size(token) + 1));
	if (!new)
	{
		g_g.exit_malloc = 1;
		free(token);
		exit(12);
	}
	return (set_expansion(token, &new, 0, 0));
}
