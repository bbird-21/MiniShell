/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:21:04 by alvina            #+#    #+#             */
/*   Updated: 2023/02/27 15:07:58 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int how_many(char *str)
{
    int i;
    int nb;

    i = 1;
    nb = 0;
    if (str[ft_strlen(str) - 1] != '/')
        nb = 1;
    while (str[i])
    {
        if (str[i] == '/')
            nb++;
        i++;
    }
    return (nb);
}

static char    *new_str(char *old, int len)
{
    int i;
    char *new;

    i = 0;
    new = malloc(sizeof(char) * len + 1);
    while (old[i] && i < len)
    {
        new[i] = old[i];
        i++;
    }
    new[i] = '\0';
    return (new);
}

static char    *back(char *pwd, char *arg)
{
    int     nb_arg;
    int     len;
    char    *new;
    char    *old;

    if (arg[0] == '/')
        return ("/");
    if (!pwd)
        return (NULL);
    nb_arg = how_many(arg);
    printf("%d\n", nb_arg);
    len = 1;
    old = pwd;
    while (nb_arg > 0 && len > 0)
    {
        len = ft_strlen(old) - 1;
        while (old[len] != '/' && len > 0)
            len--;
        if (!len)
            return ("/");
        new = new_str(old, len);
        old = new;
        nb_arg--;
    }
    return (old);
}

void    cd(char *arg)
{
    char    *pwd;
    char    *oldpwd;
    char    *dir_path;
    char    *tmp;
    

    if (!arg || (arg[0] == '~' && ft_strlen(arg) == 1)
    {
        if (ft_getenv("HOME"))
            chdir(ft_getenv("HOME"));
        exit(0);
    }
    if ((ft_strlen(arg) == 1 && arg[0] == '.') || ft_strlen(arg) == 0)
        exit(0);
    if (root_dir(arg, 0))
        dir_path = root_dir(arg, 1);
    // else if (ft_strlen(arg) == 1 && arg[0] == '-')
    // {
    //     getcwd(oldpwd, PATH_MAX);
    //     dir = ft_getenv("OLDPWD");
    // }
    else
    {
        getcwd(oldpwd, PATH_MAX);
        dir_path = join_slash(oldpwd, arg);
        free(oldpwd);
        printf("path directory = %s", dir_path);
    }
    if (chdir(dir_path) == -1)
	{
        free(dir_path);
        ft_putstr_fd("cd: ", 2);
        perror("");
        ft_putendl_fd(arg, 2);
        exit(errno);
    }
    free(dir_path);
    tmp = ft_getenv("PWD");
    oldpwd = join("OLDPWD=", tmp);
    env(3, NULL, oldpwd);
    free(tmp);
    getcwd(tmp, PATH_MAX);
    pwd = join("PWD=", tmp);
    env(3, NULL, pwd);
    free(tmp);
    free(oldpwd);
    free(pwd);
	return ;
}