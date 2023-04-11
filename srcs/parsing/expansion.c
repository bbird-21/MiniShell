/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:28:29 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/04/11 19:18:26 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	This file have to expand environment variables and apply
	differents functions in strict order depending on the
	type of token. 
	
	<State 0> remove quotes.
	<State 1> remove quotes -> magic space
	<State 2> remove quotes -> expand -> magic space
*/

static int	size_var(char **token, int *i)
{
	char	*sh_var;
	char	*var_env;
	int		nb;
	int		j;

	nb = 0;
	j = 0;
	sh_var = malloc(sizeof(char) * (get_var_size(&(*token)[*i]) + 2));
	if (!sh_var)
	{
		g.exit_malloc = 1;
		return (0);
	}
	while ((*token)[*i] && ft_isalnum((*token)[*i]))
		sh_var[j++] = (*token)[(*i)++];
	sh_var[j] = 0;
	var_env = ft_getenv(sh_var);
	if (!var_env && g.exit_malloc)
	{
		free(sh_var);
		return (0);
	}
	nb = ft_strlen(var_env);
	free(var_env);
	free(sh_var);
	return (nb);
}

int	get_exp_size(char *token)
{
	int	i;
	int	size;

	size = 0;
	i = 0;
	while (token[i])
	{
		if (token[i] == EXPAND)
		{
			i++;
			if (!ft_isalnum(token[i]))
			{
				size++;
				continue ;
			}
			size += size_var(&token, &i);
			if (g.exit_malloc == 1)
				return (0);
		}
		else
		{
			i++;
			size++;
		}
	}
	return (size);
}

static int	get_expand_var(char *token, char **expand_var, int *i, int *j)
{
	char	*sh_var;

	(*i)++;
	sh_var = malloc(sizeof(char) * (get_var_size(&token[(*i)]) + 1));
	if (!sh_var || g.exit_malloc == 1)
	{
		if (sh_var)
			free(sh_var);
		g.exit_malloc = 1;
		return (0);
	}
	while (token[(*i)] && ft_isalnum(token[(*i)]))
		sh_var[(*j)++] = token[(*i)++];
	if (token[(*i)] == '_')
	{
		free(sh_var);
		(*i)++;
		return (1);
	}
	sh_var[(*j)] = 0;
	(*j) = 0;
	(*expand_var) = ft_getenv(sh_var);
	free(sh_var);
	return (0);
}

static char	*set_expansion(char *token, char **new, int i, int k)
{
	int		j;
	char	*expand_var;

	while (token[i])
	{
		j = 0;
		if (token[i] == EXPAND)
		{
			if (g.exit_malloc)
			{
				free(expand_var);
				free(*new);
				free(token);
				return (NULL);
			}
			if (get_expand_var(token, &expand_var, &i, &j))
				continue ;
			if (!expand_var)
			{
				if (token[i - 1] == EXPAND)
					(*new)[k++] = token[i - 1];
				continue ;
			}
			while (expand_var[j])
				(*new)[k++] = expand_var[j++];
			free(expand_var);
			expand_var = NULL;
		}
		else
			(*new)[k++] = token[i++];
	}
	return ((*new)[k] = 0, free(token), *new);
}

char	*expansion(char *token)
{
	char	*new;

	new = malloc(sizeof(char) * (get_exp_size(token) + 1));
	if (!new)
		return (NULL);
	return (set_expansion(token, &new, 0, 0));
}
