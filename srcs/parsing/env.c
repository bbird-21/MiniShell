/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:24:06 by ale-sain          #+#    #+#             */
/*   Updated: 2023/04/13 18:41:47 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	creating(t_list **envp, char **env, char *arg)
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

void	cleaning(t_list **envp, char **env, char *arg)
{
	(void)env;
	(void)arg;
	clear_history();
	if (envp)
		ft_lstclear(envp, env_cleaner);
	*envp = 0;
}

void	getting(t_list **envp, char **env, char *arg)
{
	(void)env;
	(void)arg;
	(void)envp;
}

t_pf	fct(int swtch)
{
	static t_pf	tableau[7] = {
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
	t_pf			hand;

	hand = fct(swtch);
	hand(&envp, env, arg);
	return (envp);
}
