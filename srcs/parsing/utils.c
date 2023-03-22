/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:29:15 by alvina            #+#    #+#             */
/*   Updated: 2023/03/22 15:47:10 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*ft_strnstr(char *big, char *little, int len)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (!big | !little | !len)
		return (0);
	if (len > ft_strlen(big))
		return (0);
	if (little[0] == '\0')
		return (0);
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

int	ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	if (!s1 || !s2)
		return (1);
	if (n > ft_strlen(s1) || n > ft_strlen(s2))
		return (1);
	while ((i < (n - 1)) && s1[i] && s2[i] && (s1[i] == s2[i]))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != 0)
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
	if (s1)
	{
		while (s1[j])
			str[i++] = s1[j++];
		j = 0;
	}
    if (s2)
	{
		if (s2[0] != '/')
        	str[i++] = '/';
		while (s2[j])
			str[i++] = s2[j++];
	}
	str[i] = '\0';
	return (str);
}

char	*simple_join(char *s1, char *s2)
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

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}

int	ft_isalnum(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'));
}

char	*ft_strjoin(char *line, char *buffer)
{
	char	*p;
	int		i;
	int		j;

	j = 0;
	i = 0;
	p = malloc(sizeof(char) * (ft_strlen(line)
				+ ft_strlen(buffer)) + 1);
	if (!p)
		return (NULL);
	if (line != NULL)
	{
		if (line[i])
		{
			while (line[i] != 0)
			{
				p[i] = line[i];
				i++;
			}
		}
	}
	while (buffer[j])
	{
		p[i] = buffer[j];
		i++;
		j++;
	}
	p[i] = '\0';
	if (line)
		free(line);
	return (p);
}

bool	ft_strcmp(const char *s1, const char *s2)
{	
	unsigned int	i;

	if (!s1 || !s2)
		return (false);
	i = 0;
	while (s1[i] == s2[i] && (s1[i] || s2[i]))
		i++;
	if (s1[i] == s2[i])
		return (true);
	return (false);
}
