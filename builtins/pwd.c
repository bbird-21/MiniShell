/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:10:40 by alvina            #+#    #+#             */
/*   Updated: 2023/02/23 18:02:33 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void    pwd(void)
{
    ft_putendl_fd(ft_getenv("PWD"), 1);
}

int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90)
		|| (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}

int is_correct(char *str)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(str);
    if (!ft_isalpha(str[0]) && str[0] != '_')
        return (0);
    while (str[i] && str[i] != '=')
    {
        if (str[i] == '+' && str[i + 1] == '=')
            break;
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (0);
        i++;
    }
	return (1);
}

void   export(char *name)
{
    t_list  *envp;
    char    *key;    
    
    envp = handler(5, NULL, NULL);
    if (!name)
        return (print_lst(envp, print_env));
    if (!ft_strchr(name, '='))
	{
        if (!ft_getenv(name))
           handler(2, NULL, name);
        return ;
    }
    key = ft_key(name); /*cmt on parse name?*/
    if (!is_correct(name))
    {
        ft_putendl_fd("nanoshell : export : not a valid identifier", 2);
        free(key);
        return ;
    }
    if (ft_strnstr(name, "+=", ft_strlen(name))) /*dans handler 6 : parser le +, verifier si name existe, si oui append, sinon handler 2 str modifie : accepte + =*/
        handler(6, NULL, name);
    else
    {
        if (ft_getenv(key))
            handler(3, NULL, name);
        else
            handler(2, NULL, name);
    }
    free(key);
    return ;

        
    
    
} 