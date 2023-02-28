/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:42:29 by ale-sain          #+#    #+#             */
/*   Updated: 2023/02/28 18:55:01 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_exit_status;

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

void    exec(t_list *cmd_lst)
{
    print_lst(cmd_lst, print_cmd);
    ft_lstclear(&cmd_lst, cmd_cleaner);
	return ;
}

void	expansion(t_list *token_lst)
{
	return (cmd_generator(&token_lst));
}

void	token_generator(char **tab)
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
			free_tab(tab, -1);
			ft_lstclear(&t_lst, token_cleaner);
			handler(4, NULL, NULL);
			exit(0);
		}
        t_new = ft_lstnew(data);
		if (!t_new)
		{
			free_tab(tab, -1);
			ft_lstclear(&t_lst, token_cleaner);
			handler(4, NULL, NULL);
			exit(0);
		}
        t_lst = ft_lstadd_back(&t_lst, t_new);
		i++;
	}
	free_tab(tab, -1);
	if (!t_lst)
	{
		handler(4, NULL, NULL);
		exit(0);
	}
	tokenisation(&t_lst);
	if (!parse_error(t_lst))
	{
		ft_lstclear(&t_lst, token_cleaner);
		handler(4, NULL, NULL);
		return ;
	}
	return (expansion(t_lst));
}

int main(int ac, char **av, char **env)
{
	char	*str;
	
	(void)ac;
	(void)av;
	(void)env;
	g_exit_status = 0;
	// handler(0, env, NULL);
	// rl_outstream = stderr;
	while (21)
	{
        str = readline("nanoshell > ");
		ft_exit(str);
		printf("%d \n", g_exit_status);
		free(str);
		// if (!str || (str[0] == '\0' && ft_strlen(str) == 1)
		// 	|| (ft_strnstr(str, "exit", 4) && ft_strlen(str) == 4))
		// {
		// 	if (ft_strnstr(str, "exit", 4))
		// 		free(str);
		// 	handler(4, NULL, NULL);
		// 	exit(0);
		// }
		// first_split(str);
	}
}