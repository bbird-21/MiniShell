/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:21:04 by alvina            #+#    #+#             */
/*   Updated: 2023/02/18 22:08:38 by alvina           ###   ########.fr       */
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

int main(int ac, char **av)
{
    (void)ac;
    char *str;

    if (ac > 2)
    {
        ft_putendl_fd("usage : cd <absolute/relative path", 1);
        exit(2);
    }
    if (ac == 1 || ft_strnstr(av[1], "~", 1))
    {
        chdir(getenv("HOME"));
        exit(0);
    }
    if ((ft_strlen(av[1]) == 1 && av[1][0] == '.') || ft_strlen(av[1]) == 0)
        exit(0);
    if (ft_strnstr(av[1], "..", 2) || ft_strnstr(av[1], "/..", 3) || ft_strnstr(av[1], "../", 3))
        str = back(getenv("PWD"), av[1]);
    else
        str = join(getenv("PWD"), av[1]);
    //verifier si dossier ouvrable
    printf("path directory = %s", str);
    if (chdir(str) == -1)
	{
        free(str);
        ft_putstr_fd("cd: ", 2);
        perror("");
        ft_putendl_fd(av[1], 2);
        exit(errno);
    }
	exit(0);
}