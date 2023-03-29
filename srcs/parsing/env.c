/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:24:06 by ale-sain          #+#    #+#             */
/*   Updated: 2023/03/29 10:34:48 by ale-sain         ###   ########.fr       */
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
		return (NULL);
	i = 0;
	while (str[i] != '=' && str[i])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			break ;
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
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
	if (!str[i])
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(&str[i]) + 1));
	if (!new)
		return (NULL);
	while (str[i])
	{
		new[j] = str[i];
		i++;
		j++;
	}
	new[j] = '\0';
	return (new);
}

static void	modifying(t_list **envp, char **env, char *arg)
{
	t_list	*curr;
	t_env	*data;
	char	*key;

	(void)env;
	if (!(*envp) || !arg)
		return ;
	curr = *envp;
	data = (t_env *)(curr->content);
	key = ft_key(arg);
	if (!key)
		return ;
	while ((curr) && ft_strncmp(data->key, key, ft_strlen(key)))
	{
		curr = curr->next;
		if (curr)
			data = (t_env *)(curr->content);
	}
	if (!curr || ft_strlen(data->key) != ft_strlen(key))
		return (free(key));
	free(key);
	free(data->value);
	data->value = ft_value(arg);
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

static void	appending(t_list **envp, char **env, char *arg)
{
	t_list	*curr;
	t_env	*data;
	char	*key;

	(void)env;
	curr = *envp;
	data = (t_env *)curr->content;
	key = ft_key(arg);
	if (!arg || !curr)
		return ;
	while (curr && ft_strncmp(data->key, key, ft_strlen(key)))
	{
		curr = curr->next;
		if (curr)
			data = (t_env *)curr->content;
	}
	if (!curr || (ft_strlen(data->key) != ft_strlen(key)))
		return ;
	free(key);
	data->value = joining_value(data, ft_value(arg));
}

static t_env	*create_env(char *str)
{
	t_env	*data;

	data = malloc(sizeof(t_env));
	if (!data)
		return (NULL);
	data->key = ft_key(str);
	data->value = ft_value(str);
	if (!data->key)
	{
		env_cleaner(data);
		return (NULL);
	}
	return (data);
}

static void	adding(t_list **envp, char **env, char *arg)
{
	t_env	*data;
	t_list	*e_new;

	(void)env;
	if (!arg)
		return ;
	data = create_env(arg);
	if (!data)
	{
		ft_lstclear(envp, env_cleaner);
		return ;
	}
	e_new = ft_lstnew(data);
	if (!e_new)
	{
		ft_lstclear(envp, env_cleaner);
		return ;
	}
	(*envp) = ft_lstadd_back(envp, e_new);
}

static void	creating(t_list **envp, char **env, char *arg)
{
	int	i;

	(void)arg;
	i = 0;
	if (!env || !*env)
		return ;
	while (env[i])
	{
		adding(envp, env, env[i]);
		i++;
	}
}

//voir si fonction parse ou pas? la pas parser
static void	deleting(t_list **envp, char **env, char *arg)
{
	t_list	*curr;
	t_list	*prev;

	(void)env;
	curr = (*envp);
	prev = NULL;
	while ((curr) && ft_strncmp(((t_env *)(curr->content))->key, arg,
			ft_strlen(arg)))
	{
		prev = curr;
		curr = curr->next;
	}
	if (!curr || ft_strlen(((t_env *)(curr->content))->key) != ft_strlen(arg))
		return ;
	if (!prev)
	{
		prev = curr->next;
		(*envp) = prev;
	}
	else
		prev->next = curr->next;
	env_cleaner((t_env *)(curr->content));
	free(curr);
}

static void	cleaning(t_list **envp, char **env, char *arg)
{
	(void)env;
	(void)arg;
	if (envp)
		ft_lstclear(envp, env_cleaner);
	*envp = 0;
}

static void	getting(t_list **envp, char **env, char *arg)
{
	(void)env;
	(void)arg;
	(void)envp;
}

static pf	fct(int swtch)
{
	static pf tableau[7] = {
		creating,
		deleting,
		adding,
		modifying,
		cleaning,
		getting,
		appending};
	return (tableau[swtch]);
}

t_list	*handler(int swtch, char **env, char *arg)
{
	static t_list	*envp;
	pf				hand;

	hand = fct(swtch);
	hand(&envp, env, arg);
	return (envp);
}

