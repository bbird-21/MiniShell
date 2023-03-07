/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:49:16 by ale-sain          #+#    #+#             */
/*   Updated: 2023/02/28 20:50:28 by ale-sain         ###   ########.fr       */
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
	rl_outstream = stderr;
	while (21)
	{
        str = readline("nanoshell > ");
		if (!str || (str[0] == '\0' && ft_strlen(str) == 1)
			|| (ft_strnstr(str, "exit", 4) && ft_strlen(str) == 4))
		{
			if (ft_strnstr(str, "exit", 4))
				free(str);
			handler(4, NULL, NULL);
			exit(0);
		}
		first_split(str);
	}
}
