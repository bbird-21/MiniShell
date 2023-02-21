/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:24:06 by ale-sain          #+#    #+#             */
/*   Updated: 2023/02/21 14:30:21 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*ft_key(char *str)
{
	int		i;
	char	*new;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '=' && str[i])
		i++;
	new = malloc(sizeof(char) * i + 1);
	// new = NULL;
	if (!new)
		return (NULL);
	i = 0;
	while (str[i] != '=' && str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

static char	*ft_value(char *str)
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
	// new = NULL;
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

static void	modifying(t_env **envp, char **env, char *arg)
{
	t_env	*curr;
	char	*key;
	(void)env;

	if (!(*envp) || !arg)
		return ;
	curr = *envp;
	key = ft_key(arg);
	if (!key)
		return ;
	while ((curr) && !ft_strnstr(curr->key, key, ft_strlen(key)))
		curr = curr->next;
	free(key);
	if (!curr)
		return ;
	free(curr->value);
	curr->value = ft_value(arg);
}

static void	adding(t_env **envp, char **env, char *arg)
{
	t_env	*new;
	(void)env;

	new = malloc(sizeof(t_env));
	// new = NULL;
	if (!new)
	{
		if (envp)
			ft_envclear(envp);
		return ;
	}
	new->key = ft_key(arg);
	if (!new->key)
	{
		if (envp)
			ft_envclear(envp);
		free(new);
		return ;
	}
	new->value = ft_value(arg);
	if (!new->value)
	{
		if (envp)
			ft_envclear(envp);
		free(new->key);
		free(new);
		return ;
	}
	new->next = NULL;
	env_add_back(envp, new);
}

static void	creating(t_env **envp, char **env, char *arg)
{
	(void)arg;
	int	i;

	i = 0;
	while (env[i])
	{
		adding(envp, env, env[i]);
		i++;
	}
}

static void	del(t_env *lst)
{
	free(lst->key);
	free(lst->value);
	free(lst);
}

static void	deleting(t_env **envp, char **env, char *arg)
{
	t_env	*curr;
	t_env	*prev;
	(void)env;

	curr = (*envp);
	prev = NULL;
	while ((curr) && !ft_strnstr(curr->key, arg, ft_strlen(arg)))
	{
		prev = curr;
		curr = curr->next;
	}
	if (!curr)
		return ;
	if (!prev)
	{
		prev = curr->next;
		(*envp) = prev;
	}
	else
		prev->next = curr->next;
	del(curr);
}

static pf	fct(int swtch)
{
	static pf	tableau[4] = {
		creating,
		deleting,
		adding,
		modifying
	};
	return (tableau[swtch]);
}

t_env	*handler(int swtch, char **env, char *arg)
{
	static t_env	*envp;
	pf hand;

	if (!env || !arg)
		return (NULL);
	hand = fct(swtch);
	hand(&envp, env, arg);
	return (envp);
}

