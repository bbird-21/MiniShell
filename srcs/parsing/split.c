/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 23:34:30 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/31 13:32:23 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	nb_words(char const *s, char c)
{
	int	nb_words;
	int	check_word;
	int	i;

	i = 0;
	check_word = 1;
	nb_words = 0;
	while (s[i])
	{
		if (s[i] != c && check_word)
		{
			nb_words++;
			check_word = 0;
		}
		else if (s[i] == c)
			check_word = 1;
		i++;
	}
	return (nb_words);
}

static char	*ft_initword(char *src, size_t endWord, size_t nbchar, char c)
{
	size_t	i;
	int		begin;
	char	*word;

	begin = (endWord - nbchar);
	if (begin < 0)
		begin -= begin;
	i = 0;
	word = malloc(sizeof(char) * (nbchar + 1));
	if (!word)
		return (NULL);
	if (src[begin] == c || begin < 0)
		begin++;
	while (src[begin] && i < nbchar)
		word[i++] = src[begin++];
	word[i] = '\0';
	return (word);
}

static void	extra_init(int *index, int *nbchar, int *i)
{
	*i = 0;
	*index = 0;
	*nbchar = 0;
}

char	**protection(char *s)
{
	char	**split;

	if (!s)
		return (NULL);
	split = malloc(sizeof(char *) * 1);
	split[0] = malloc(1);
	split[0][0] = 0;
	return (split);
}

char	**ft_split(char *s, char c)
{
	char	**split;
	int		i;
	int		nbchar;
	int		index;

	if (!s || !s[0])
		return (protection(s));
	extra_init(&index, &nbchar, &i);
	split = (char **)malloc(sizeof(char *) * (nb_words(s, c) + 1));
	if (!split)
	{
		g.exit_malloc = 1;
		return (NULL);
	}
	while (i < ft_strrlen((char *)s))
	{
		if (s[i] != c)
			nbchar++;
		if ((s[i] == c || i == ft_strrlen((char *)s) - 1) && nbchar > 0)
		{
			split[index++] = ft_initword((char *)s, i, nbchar, c);
			if (!split[index - 1])
			{
				free_tab(split, index -1);
				g.exit_malloc = 1;
				return (NULL);
			}
			nbchar = 0;
		}
		i++;
	}
	split[index] = NULL;
	return (split);
}
