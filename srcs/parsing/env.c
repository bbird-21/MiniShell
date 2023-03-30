/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:24:06 by ale-sain          #+#    #+#             */
/*   Updated: 2023/03/30 11:36:44 by alvina           ###   ########.fr       */
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

pf	fct(int swtch)
{
	static pf	tableau[7] = {
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
