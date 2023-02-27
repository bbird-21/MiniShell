/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:42:29 by ale-sain          #+#    #+#             */
/*   Updated: 2023/02/27 21:38:44 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*create_token(char *str)
{
	t_token	*data;

	data = malloc(sizeof(t_token));
	if (!data)
		return (NULL);
	data->value = ft_strdup(str);
	if (!data->value)
	{
		free(data);
		return (NULL);
	}
	data->type = 0;
	return (data);
}

t_list	*token_generator(char **tab)
{
	int		i;
	t_token *data;
	t_list	*t_new;
	t_list	*t_lst;

	i = 0;
	t_lst = NULL;
	while (tab[i])
	{
		data = create_token(tab[i]);
		if (!data)
		{
			ft_lstclear(&t_lst, token_cleaner);
			return (0);
		}
        t_new = ft_lstnew(data);
		if (!t_new)
		{
			ft_lstclear(&t_lst, token_cleaner);
			return (0);
		}
        t_lst = ft_lstadd_back(&t_lst, t_new);
		i++;
	}
	return (t_lst);
}

void	minishell(char *str)
{
	char 	**tab;
	t_list *token_lst;

	tab = first_split(str);
	if (!tab)
	{
		free(str);
		handler(4, NULL, NULL);
		exit(0);
	}
	token_lst = token_generator(tab);
	free_tab(tab, -1);
	free(str);
	if (!token_lst)
	{
		handler(4, NULL, NULL);
		exit(0);
	}
	tokenisation(&token_lst);
	if (!parse_error(token_lst))
	{
		ft_lstclear(&token_lst, token_cleaner);
		handler(4, NULL, NULL);
		return ;
	}
	print_lst(token_lst, print_token);
    cmd_generator(&token_lst);
}

int main(int ac, char **av, char **env)
{
	// char	*str;
	// t_list	*envp;
	
	(void)ac;
	(void)av;
	(void)env;
	// cd(av[1]);
	handler(0, env, NULL);
	// unset(av[1]);
	pwd();
	cd(av[1]);
	char *pwd = ft_getenv("PWD");
	char *oldpwd = ft_getenv("OLDPWD");
	printf("pwd = %s, oldpwd = %s \n", pwd, oldpwd);
	free(pwd);
	free(oldpwd);
	// envp = handler(2, env, av[1]);
	// envp = handler(1, env, "CLE");
	// envp = handler(3, env, "CLE=lol");
	// print_lst(envp, print_env);
	// export(av[1]);
	//  envp = handler(3, env, av[1]);
	// ft_env();
	handler(4, NULL, NULL);
	// printf("%s \n", ft_getenv("CLE="));
	// rl_outstream = stderr;
	// while (21)
	// {
    //     str = readline("nanoshell > ");
	// 	if (!str || (str[0] == '\0' && ft_strlen(str) == 1)
	// 		|| (ft_strnstr(str, "exit", 4) && ft_strlen(str) == 4))
	// 	{
	// 		if (ft_strnstr(str, "exit", 4))
	// 			free(str);
	// 		handler(4, NULL, NULL);
	// 		exit(0);
	// 	}
	// 	minishell(str);
	// }
}