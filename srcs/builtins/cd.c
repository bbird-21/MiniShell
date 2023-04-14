/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:21:04 by alvina            #+#    #+#             */
/*   Updated: 2023/04/15 00:10:56 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <linux/limits.h>

static char	*root_dir(void)
{
	char	*res;

	res = malloc(sizeof(char) * 2);
	res[0] = '/';
	res[1] = '\0';
	return (res);
}

static char	*dir_path(char *arg)
{
	char	*path;
	char	*oldpwd;

	if (!arg || (arg[0] == '~' && ft_strlen(arg) == 1))
	{
		path = ft_getenv("HOME");
		if (!path)
			return (NULL);
	}
	else if ((ft_strlen(arg) == 1 && arg[0] == '.') || ft_strlen(arg) == 0)
		return (NULL);
	else if ((ft_strlen(arg) == 1 && arg[0] == '/') || (ft_strlen(arg) == 2
			&& arg[0] == '/' && arg[1] == '.') || (ft_strlen(arg) == 3
			&& arg[0] == '/' && arg[1] == '.' && arg[2] == '.'))
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

static void	set_oldpwd(void)
{
	char	*tmp;
	char	*oldpwd;

	tmp = ft_getenv("PWD");
	oldpwd = simple_join("OLDPWD=", tmp);
	handler(3, NULL, oldpwd);
	free(tmp);
	free(oldpwd);
}

static void	set_pwd(void)
{
	char	*tmp;
	char	*pwd;

	pwd = NULL;
	tmp = malloc(sizeof(char) * PATH_MAX);
	if (getcwd(tmp, PATH_MAX))
		pwd = simple_join("PWD=", tmp);
	handler(3, NULL, pwd);
	free(tmp);
	free(pwd);
}

void	cd(char **arg)
{
	char	*path;
	int		flag;

	flag = 0;
	if (!check_arg(arg, 1, "cd"))
		return (return_code(1));
	path = dir_path(arg[0]);
	if (!path)
		return (return_code(0));
	if (arg && *arg)
	{
		if (chdir(arg[0]) == -1)
			flag = 1;
	}
	if (flag == 1 || !arg)
	{
		if (chdir(path) == -1)
		{
			free(path);
			ft_putstr_fd("cd: ", 2);
			ft_putstr_fd(arg[0], 2);
			return (perror(" "), return_code(1));
		}
	}
	return (free(path), set_oldpwd(), set_pwd(), return_code(0));
}
