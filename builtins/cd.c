/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:21:04 by alvina            #+#    #+#             */
/*   Updated: 2023/02/27 21:39:27 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*simple_join(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!str)
		return (NULL);
	if (s1)
	{
		while (s1[j])
			str[i++] = s1[j++];
		j = 0;
	}
    if (s2)
	{
		while (s2[j])
			str[i++] = s2[j++];
	}
	str[i] = '\0';
	return (str);
}

char    *root_dir(void)
{
    char *res;

    res = malloc(sizeof(char) * 2);
    res[0] = '/';
    res[1] = '\0';
    return (res);
}

void    cd(char *arg)
{
    char    *pwd;
    char    *oldpwd;
    char    *dir_path;
    char    *tmp;
    
    if (!arg || (arg[0] == '~' && ft_strlen(arg) == 1))
    {
        dir_path = ft_getenv("HOME");
        if (!dir_path)
            return ;
    }
    else if ((ft_strlen(arg) == 1 && arg[0] == '.') || ft_strlen(arg) == 0)
        return ;
    else if ((ft_strlen(arg) == 1 && arg[0] == '/')
        || (ft_strlen(arg) == 2 && arg[0] == '/' && arg[1] == '.')
        || (ft_strlen(arg) == 3 && arg[0] == '/' && arg[1] == '.' && arg[2] == '.'))
        dir_path = root_dir();
    else if (ft_strlen(arg) == 1 && arg[0] == '-')
        dir_path = ft_getenv("OLDPWD");
    else
    {
        oldpwd = malloc(sizeof(char) * PATH_MAX);
        getcwd(oldpwd, PATH_MAX);
        dir_path = join(oldpwd, arg);
        free(oldpwd);
    }
    printf("dir path = %s \n", dir_path);
    if (chdir(arg) == -1)
    {
        if (chdir(dir_path) == -1)
        {
            free(dir_path);
            ft_putstr_fd("cd: ", 2);
            ft_putstr_fd(arg, 2);
            perror(" ");
            return ;
        }
    }
    free(dir_path);
    tmp = ft_getenv("PWD");
    oldpwd = simple_join("OLDPWD=", tmp);
    handler(3, NULL, oldpwd);
    free(tmp);
    free(oldpwd);
    tmp = malloc(sizeof(char) * PATH_MAX);
    getcwd(tmp, PATH_MAX);
    pwd = simple_join("PWD=", tmp);
    handler(3, NULL, pwd);
    free(tmp);
    free(pwd);
	return ;
}