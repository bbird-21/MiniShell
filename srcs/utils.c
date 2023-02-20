/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:29:15 by alvina            #+#    #+#             */
/*   Updated: 2023/02/20 22:39:51 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
		i++;
    write(fd, s, i);
}

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

t_token	*token_add_back(t_token **lst, t_token *new)
{
	t_token	*last;

	last = NULL;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = token_last(*lst);
		last->next = new;
	}
	return (*lst);
}

t_cmd	*cmd_add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last;

	last = NULL;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = cmd_last(*lst);
		last->next = new;
	}
	return (*lst);
}

t_env	*env_add_back(t_env **lst, t_env *new)
{
	t_env	*last;

	last = NULL;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = env_last(*lst);
		last->next = new;
	}
	return (*lst);
}

t_token	*token_last(t_token *lst)
{
	if (lst->next)
	{
		while (lst && lst->next)
			lst = lst->next;
	}
	return (lst);
}

t_cmd	*cmd_last(t_cmd *cmd)
{
	if (cmd->next)
	{
		while (cmd && cmd->next)
			cmd = cmd->next;
	}
	return (cmd);
}

t_env	*env_last(t_env *cmd)
{
	if (cmd->next)
	{
		while (cmd && cmd->next)
			cmd = cmd->next;
	}
	return (cmd);
}

char	*ft_strnstr(char *big, char *little, int len)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (!big)
		return (0);
	if (len > ft_strlen(big))
		return (0);
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j]
			&& (i + j) < len && big[i + j])
		{
			j++;
			if (little[j] == '\0')
			{
				return ((char *)&big[i]);
			}
		}
		i++;
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s)
{
	int		i;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
		i++;
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		return (0);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*join(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 2);
	if (!str)
		return (NULL);
	while (s1[j])
		str[i++] = s1[j++];
	j = 0;
    if (s2[0] != '/')
        	str[i++] = '/';
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}
