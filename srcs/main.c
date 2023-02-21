/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:42:29 by ale-sain          #+#    #+#             */
/*   Updated: 2023/02/21 18:53:06 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*create_token(char *str)
{
	t_token	*lst;
	static int flag;

	lst = malloc(sizeof(t_token));
	if (flag)
		return (NULL);
	flag++;
	lst->value = ft_strdup(str);
	lst->type = 0;
	lst->next = NULL;
	if (!lst->value)
	{
		free(lst);
		return (NULL);
	}
	return (lst);
}

void	*new_token(t_token **lst, char *str)
{
	t_token		*new;

	new = create_token(str);
	if (!new)
		return (NULL);
	return (token_add_back(lst, new));
}

t_token	*token_generator(char **tab)
{
	int		i;
	t_token *lst;
	t_token *head;

	i = 0;
	lst = NULL;
	head = NULL;
	while (tab[i])
	{
		if (!new_token(&lst, tab[i]))
		{
			ft_lstclear(&head);
			return (0);
		}
		if (i == 0)
			head = lst;
		i++;
	}
	return (head);
}

void	minishell(char *str)
{
	char 	**tab;
	t_token *lst;
// static int flag;

	tab = first_split(str);
	if (!tab)
	{
		free(str);
		exit(0);
	}
	// int i = 0;
	// while (tab[i])
	// 	printf("%s \n", tab[i++]);
// if (flag == 0)
		lst = token_generator(tab);
// else
// 	lst = NULL;
// flag++;
	if (!lst)
	{
		free_tab(tab, -1);
		free(str);
		exit(0);
	}
	print_lst(lst);
	// tokenisation(&lst);
	free_tab(tab, -1);
	free(str);
	// if (!parse_error(lst))
	// {
		ft_lstclear(&lst);
	// 	return ;
	// }
    // cmd_generator(&lst);
}

int main(int ac, char **av, char **env)
{
	char	*str;
	// t_env	*envp;
	
	(void)ac;
	(void)av;
	(void)env;

	// handler(0, env, NULL);	
	// envp = handler(2, env, av[1]);
	// envp = handler(1, env, "PATH");
	// envp = handler(3, env, "PATH=dhdh");
	// print_env(envp);
	while (21)
	{
        str = readline("nanoshell > ");
		if (!str || str[0] == '\0' || (ft_strnstr(str, "exit", 4) && ft_strlen(str) == 4))
		{
			if (ft_strnstr(str, "exit", 4))
				free(str);
			exit(0);
		}
		minishell(str);
	}
	// ft_envclear(&envp);
}