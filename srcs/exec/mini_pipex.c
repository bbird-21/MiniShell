/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:38:56 by ale-sain          #+#    #+#             */
/*   Updated: 2023/03/15 19:02:38 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int counter(t_list *cmd)
{
    int i;
    t_list *tmp;

    i = 0;
    tmp = cmd;
    if (!tmp)
        return (0);
    while (tmp)
    {
        tmp = tmp->next;
        i++;
    }
    return (i);
}

static ptr_fun	funct(int flag)
{
	static ptr_fun	tableau[7] = {
		cd,
		echo,
		ft_env,
		ft_exit,
		export,
		pwd,
        unset
	};
	return (tableau[flag]);
}

void    execve_builtin(int flag, char **arg)
{
	ptr_fun  exec;

    if (flag == -2)
        return ;
    exec = funct(flag);
	exec(&arg[1]);
}

int is_builtin(char *str, int pipe)
{
    if (ft_strnstr(str, "env", 3) && ft_strlen(str) == 3)
        return (2);
    if (ft_strnstr(str, "echo", 4) && ft_strlen(str) == 4)
        return (1);
    if (ft_strnstr(str, "pwd", 3) && ft_strlen(str) == 3)
        return (5);
    if (ft_strnstr(str, "cd", 2) && ft_strlen(str) == 2)
    {
        if (pipe)
            return (-2);
        return (0);
    }
    if (ft_strnstr(str, "exit", 4) && ft_strlen(str) == 4)
    {
        if (pipe)
            return (-2);
        return (3);
    }
    if (ft_strnstr(str, "export", 6) && ft_strlen(str) == 6)
    {
        if (pipe)
            return (-2);
        return (4);
    }
    if (ft_strnstr(str, "unset", 5) && ft_strlen(str) == 5)
    {
        if (pipe)
            return (-2);
        return (6);
    }
    return (-1);
}

void mini_pipex(t_list *cmd)
{
    int     pfd[2];
    int     pid1;
    int     pid2;
    char    **env;
    char    **arg;
    t_cmd   *content;
    int     nb;
    
    nb = counter(cmd);
    if (!nb)
        return ;
    env = translator(handler(5, NULL, NULL), trans_env);
    content = (t_cmd *)cmd->content;
	arg = translator(content->arg, trans_token);

    if (nb == 1)
    {
        if (is_builtin(arg[0], 0) != -1)
        {
            if (content->infile >= 0)
                dup2(content->infile, 0);
            if (content->outfile >= 0)
                dup2(content->outfile, 1);
            execve_builtin(is_builtin(arg[0], 0), arg);
            return ;
        }
    }
    
    pipe(pfd);
    pid1 = fork();
    if (pid1 == 0)
    {
        if (content->infile >= 0)
            dup2(content->infile, 0);
        if (content->outfile >= 0)
            dup2(content->outfile, 1);
        else if (nb > 1)
            dup2(pfd[1], 1);
        close(pfd[0]);
        close(pfd[1]);
        if (is_builtin(arg[0], 1) != -1)
            execve_builtin(is_builtin(arg[0], 1), arg);
        else
            execve(arg[0], arg, env);
    }
    free_tab(arg, -1);
    if (nb > 1)
    {
        cmd = cmd->next;
        content = (t_cmd *)cmd->content;
        arg = translator(content->arg, trans_token);

        pid2 = fork();
        if (pid2 == 0)
        {
            if (content->infile >= 0)
                dup2(content->infile, 0);
            else
                dup2(pfd[0], 0);
            if (content->outfile >= 0)
                dup2(content->outfile, 1);
            close(pfd[0]);
            close(pfd[1]);
            if (is_builtin(arg[0], 1) != -1)
                execve_builtin(is_builtin(arg[0], 1), arg);
            else
                execve(arg[0], arg, env);
        }
    }
    close(pfd[0]);
    close(pfd[1]);
    waitpid(pid1, NULL, 0);
    if (nb > 1)
        waitpid(pid2, NULL, 0);
    
    ft_lstclear(&cmd, cmd_cleaner);
    return ;
}