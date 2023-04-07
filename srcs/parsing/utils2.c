/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:59:50 by alvina            #+#    #+#             */
/*   Updated: 2023/04/07 09:37:31 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*join(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 2);
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
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!str)
	{
		g.exit_malloc = 1;
		return (NULL);
	}
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

char	*ft_strjoin(char *line, char *buffer)
{
	char	*p;
	int		i;
	int		j;

	j = 0;
	i = -1;
	p = malloc(sizeof(char) * (ft_strlen(line) + ft_strlen(buffer)) + 1);
	if (!p)
		return (NULL);
	if (line != NULL)
	{
		while (line[++i])
			p[i] = line[i];
		free(line);
	}
	if (buffer)
	{
		while (buffer[j])
			p[i++] = buffer[j++];
	}
	p[i] = '\0';
	return (p);
}

bool	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	if (!s1 || !s2)
		return (false);
	i = 0;
	while ((s1[i] || s2[i]) && s1[i] == s2[i])
		i++;
	if (s1[i] == s2[i])
		return (true);
	return (false);
}
