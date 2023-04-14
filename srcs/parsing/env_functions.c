/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:41:32 by alvina            #+#    #+#             */
/*   Updated: 2023/04/14 23:28:32 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	appending(t_list **envp, char **env, char *arg)
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
	while (curr && (ft_strncmp(data->key, key, ft_strlen(key))
			|| (ft_strlen(data->key) != ft_strlen(key))))
	{
		curr = curr->next;
		if (curr)
			data = (t_env *)curr->content;
	}
	if (!curr || (ft_strlen(data->key) != ft_strlen(key)))
		return ;
	free(key);
	data->value = joining_value(data, ft_value(arg));
	if (g_g.exit_malloc)
		exit(12);
}

void	adding(t_list **envp, char **env, char *arg)
{
	t_env	*data;
	t_list	*e_new;

	(void)env;
	if (!arg)
		return ;
	data = create_env(arg);
	if (g_g.exit_malloc)
	{
		ft_lstclear(envp, env_cleaner);
		exit(12);
	}
	e_new = ft_lstnew(data);
	if (g_g.exit_malloc)
	{
		ft_lstclear(envp, env_cleaner);
		env_cleaner(data);
		exit(12);
	}
	(*envp) = ft_lstadd_back(envp, e_new);
}

void	deleting(t_list **envp, char **env, char *arg)
{
	t_list	*curr;
	t_list	*prev;

	(void)env;
	curr = (*envp);
	prev = NULL;
	while (curr && (ft_strncmp(((t_env *)(curr->content))->key, arg,
			ft_strlen(arg)) || ft_strlen(((t_env *)(curr->content))->key)
			!= ft_strlen(arg)))
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

void	modifying(t_list **envp, char **env, char *arg)
{
	t_list	*curr;
	char	*key;

	(void)env;
	if (!(*envp) || !arg)
		return ;
	curr = *envp;
	key = ft_key(arg);
	if (g_g.exit_malloc)
		exit(12);
	while ((curr) && (ft_strncmp(((t_env *)(curr->content))->key, key,
			ft_strlen(key)) || (ft_strlen(((t_env *)(curr->content))->key)
		!= ft_strlen(key))))
		curr = curr->next;
	if (!curr || ft_strlen(((t_env *)(curr->content))->key) != ft_strlen(key))
		return (free(key));
	free(key);
	free(((t_env *)(curr->content))->value);
	((t_env *)(curr->content))->value = ft_value(arg);
	if (g_g.exit_malloc)
		exit(12);
}
