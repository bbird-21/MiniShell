/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:44:10 by alvina            #+#    #+#             */
/*   Updated: 2023/04/21 00:18:38 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *name)
{
	t_list	*envp;
	t_env	*data;

	envp = handler(5, NULL, NULL);
	if (!name || !envp)
		return (NULL);
	data = (t_env *)envp->content;
	while (envp && !ft_strcmp(data->key, name))
	{
		envp = envp->next;
		if (envp)
			data = (t_env *)envp->content;
	}
	if (!envp || ft_strlen(name) != ft_strlen(data->key))
	{
		ft_lstclear(&envp, env_cleaner);
		return (NULL);
	}
	return (ft_strdup(data->value));
}

char	*ft_key(char *str)
{
	int		i;
	char	*new;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '=' && str[i])
		i++;
	if (str[i - 1] == '+')
		i--;
	new = malloc(sizeof(char) * i + 1);
	if (!new)
	{
		g_g.exit_malloc = 1;
		exit(12);
	}
	i = 0;
	while (str[i] != '=' && str[i])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			break ;
		new[i] = str[i];
		i++;
	}
	return (new[i] = '\0', new);
}

char	*ft_value(char *str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	while (str[i] != '=' && str[i])
		i++;
	if (!str[i])
		return (NULL);
	i++;
	new = malloc(sizeof(char) * (ft_strlen(&str[i]) + 1));
	if (!new)
	{
		g_g.exit_malloc = 1;
		exit(12);
	}
	while (str[i])
	{
		new[j] = str[i];
		i++;
		j++;
	}
	new[j] = '\0';
	return (new);
}

char	*joining_value(t_env *data, char *value)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char *) * ft_strlen(data->value) + ft_strlen(value)
			+ 1);
	if (data->value)
	{
		while (data->value[i])
		{
			new[i] = (data->value)[i];
			i++;
		}
	}
	if (value)
	{
		while (value[j])
			new[i++] = value[j++];
	}
	new[i] = '\0';
	free(data->value);
	free(value);
	return (new);
}

t_env	*create_env(char *str)
{
	t_env	*data;

	data = malloc(sizeof(t_env));
	if (!data)
	{
		g_g.exit_malloc = 1;
		exit(12);
	}
	data->key = ft_key(str);
	data->value = ft_value(str);
	if (g_g.exit_malloc == 1)
	{
		free(data->key);
		free(data->value);
		env_cleaner(data);
		exit(12);
	}
	return (data);
}
