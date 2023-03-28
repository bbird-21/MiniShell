/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:28:29 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/28 15:59:13 by ale-sain         ###   ########.fr       */
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

char	*remove_quotes(char *str)
{
	char	*new;
	char	state_char;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * ft_strlen(str) - 1);
	state_char = str[i];
	str++;
	while (str[i] && str[i] != state_char)
	{
		new[i] = str[i]; // i++ tout a droite
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
	while (str[i] && ft_isalnum(str[i]))
	{
		i++;
		vr_size++;
	}
	return (vr_size);
}

int	get_exp_size(char *token)
{
	int		i;
	int		j;
	int		size;
	char	*sh_var;
	char	*var_env;

	size = 0;
	i = 0;
	while (token[i])
	{
		j = 0;
		if (token[i] == EXPAND)
		{
			i++;
			if (!ft_isalnum(token[i]))
			{
				size++;
				continue ;
			}
			sh_var = malloc(sizeof(char) * (get_var_size(&token[i]) + 2));
			while (token[i] && ft_isalnum(token[i]))
				sh_var[j++] = token[i++];
			sh_var[j] = 0;
			var_env = ft_getenv(sh_var);
			size += ft_strlen(var_env);
			free(var_env);
			free(sh_var);
			sh_var = NULL;
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

static char	*set_expansion(char *token, char **new)
{
	int		i;
	int		j;
	int		k;
	char	*expand_var;

	i = 0;
	k = 0;
	(*new) = malloc(sizeof(char) * (get_exp_size(token) + 1));
	while (token[i])
	{
		j = 0;
		if (token[i] == EXPAND)
		{
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
	(*new)[k] = 0;
	free(token);
	i = 0;
	// while (new[i])
	// 	printf("%c \n", new[i++]);
	// printf("%s \n", new[i]);
	return (*new);
}

char	*expansion(char *token)
{
	char	*new;

	return (set_expansion(token, &new));
}

char	*state_00(char *str)
{
	return (expansion(str));
}

char	*state_01(char *str)
{
	char	*new;

	new = remove_quotes(str);
	magic_space(new);
	free(str);
	return (new);
}

char	*state_02(char *str)
{
	char	*new;
	char	*new2;

	new = remove_quotes(str);
	new2 = expansion(new);
	magic_space(new2);
	free(str);
	return (new2);
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

static t_fp_exp	handling_table(unsigned char state)
{
	static t_fp_exp table[3] = {
		state_00,
		state_01,
		state_02};
	return (table[state]);
}

char	*do_job(char *str)
{
	t_fp_exp	fp;

	if (str)
		fp = handling_table(get_state(str[0]));
	else
		return (NULL);
	return (fp(str));
}
