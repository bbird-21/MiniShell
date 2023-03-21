/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:49:16 by ale-sain          #+#    #+#             */
/*   Updated: 2023/03/21 13:35:03 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

int main(int ac, char **av, char **env)
{
	char	*str;
	
	(void)ac;
	(void)av;
	(void)env;
	g_exit_status = 0;
	handler(0, env, NULL);
	// char **tab = translator(handler(5, NULL, NULL), trans_env);
	// int i = 0;
	// while (tab[i])
	// 	printf("%s \n", tab[i++]);
	rl_outstream = stderr;
	while (21)
	{
        str = readline("femtoshell > ");
		if (!str || (str[0] == '\0' && ft_strlen(str) == 1))
		{
			handler(4, NULL, NULL);
			exit(0);
		}
		first_split(str);
	}
}
