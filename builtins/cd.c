/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:21:04 by alvina            #+#    #+#             */
/*   Updated: 2023/02/28 12:48:00 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char    *root_dir(void)
{
    char *res;

    res = malloc(sizeof(char) * 2);
    res[0] = '/';
    res[1] = '\0';
    return (res);
}

static char    *dir_path(char *arg)
{
    char    *path;
    char    *oldpwd;

    if (!arg || (arg[0] == '~' && ft_strlen(arg) == 1))
    {
        path = ft_getenv("HOME");
        if (!path)
            return (NULL);
    }
    else if ((ft_strlen(arg) == 1 && arg[0] == '.') || ft_strlen(arg) == 0)
        return (NULL);
    else if ((ft_strlen(arg) == 1 && arg[0] == '/')
        || (ft_strlen(arg) == 2 && arg[0] == '/' && arg[1] == '.')
        || (ft_strlen(arg) == 3 && arg[0] == '/' && arg[1] == '.' && arg[2] == '.'))
        path = root_dir();
    else if (ft_strlen(arg) == 1 && arg[0] == '-')
        path = ft_getenv("OLDPWD");
    else
    {
        oldpwd = malloc(sizeof(char) * PATH_MAX);
        getcwd(oldpwd, PATH_MAX);
        path = join(oldpwd, arg);
        free(oldpwd);
    }
    return (path);
}

static void    set_oldpwd(void)
{
    char    *tmp;
    char    *oldpwd;

    tmp = ft_getenv("PWD");
    oldpwd = simple_join("OLDPWD=", tmp);
    handler(3, NULL, oldpwd);
    free(tmp);
    free(oldpwd);
}

static void    set_pwd(void)
{
    char    *tmp;
    char    *pwd;

    tmp = malloc(sizeof(char) * PATH_MAX);
    getcwd(tmp, PATH_MAX);
    pwd = simple_join("PWD=", tmp);
    handler(3, NULL, pwd);
    free(tmp);
    free(pwd);
}

void    cd(char *arg)
{
    char    *path;
    
    path = dir_path(arg);
    if (!path)
        return ;
    if (chdir(arg) == -1)
    {
        if (chdir(path) == -1)
        {
            free(path);
            ft_putstr_fd("cd: ", 2);
            ft_putstr_fd(arg, 2);
            perror(" ");
            return ;
        }
    }
    free(path);
    set_oldpwd();
    set_pwd();
	return ;
}