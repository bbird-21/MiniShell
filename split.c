/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 09:55:05 by alvina            #+#    #+#             */
/*   Updated: 2023/02/13 20:35:18 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**free_tab(char **tab, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(tab[i]);
		i++;
	}
	return (NULL);
}

static int	length(char *str, int *state)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (*state == 0 && is_separator(&str[i]))
			return (i);
		i++;
		*state = changing_state(str[i], *state);
	}
	return (i);
}

int    wording_sep(char *str, char ***tab, int j, int (*f)(char *))
{
    int i;

    i = 0;
    (*tab)[j] = malloc(sizeof(char) * (f(str) + 1));
    if (!(*tab)[j])
		return (free_tab(*tab, j), 0);
	while (f(&str[i]) && str[i])
	{
		(*tab)[j][i] = str[i];
		i++;
	}
	(*tab)[j][i] = '\0';
	return (i);
}

int		wording_other(char *str, char ***tab, int j, int *state)
{
	int	i;
	int	len;

	i = 0;
	len = length(str, state);
	(*tab)[j] = malloc(sizeof(char) * len + 1);
	if (!(*tab)[j])
		return (free_tab(*tab, j), 0);
	while (i < len)
	{
		(*tab)[j][i] = str[i];
		i++;
	}
	(*tab)[j][i] = '\0';
	return (i);
}

char	**splitting(char **tab, char *str, int state)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (str[i])
	{

        state = changing_state(str[i], state);
        if (state == 0 && is_separator(&str[i]))
        {
            if (!is_space(&str[i]))
            {
                if (is_pipe(&str[i]))
				{
                    i += wording_sep(&str[i], &tab, j, is_pipe);
				}
				else
                    i += wording_sep(&str[i], &tab, j, is_red);
			    j++;
            }
			else
				i++;
        }
		else if (str[i] != ' ' || state != 0)
		{
			i += wording_other(&str[i], &tab, j, &state);
			j++;
		}
		else
			i++;
	}
	tab[j] = '\0';
	return (tab);
}

char	**first_split(char *str)
{
	char	**tab;
    int     state;

    state = 0;
	if (!str || str[0] == 0)
		return (NULL);
	if (count_words(str) == 0)
		return (NULL);
	tab = (char **) malloc(sizeof(char *) * (count_words(str) + 1));
	if (!tab)
		return (NULL);
	return (splitting(tab, str, state));
}

void	*generator_token(t_token **lst, char *str)
{
	t_token		*new;

	new = ft_lstnew(str);
	if (!new)
		return (NULL);
	return (ft_lstadd_back(lst, new));
}

void	print_lst(t_token *lst)
{
	while (lst)
	{
		printf("%s ", lst->value);
		printf("%d\n", lst->type);
		lst = lst->next;
	}
}

t_token	*generator(char **tab)
{
	int	i;
	t_token *lst;
	t_token *head;

	i = 0;
	lst = NULL;
	while (tab[i])
	{
		// if (!generator_token(&tok, tab[i]))
		// {
		// 	if (!tok)
		// 		return (0);
		// 	ft_lstclear(&tok->head, cleanator);
		// 	return (0);
		// }
		generator_token(&lst, tab[i]);
		if (i == 0)
			head = lst;
		i++;
	}
	return (head);
}

int	syntax_error(char **tab)
{
	return (0);
}

int main()
{
	char	*str;
	char **tab;
	t_token *lst;
	t_token *head;
	size_t	size;
	int i = 0;

	ft_putstr_fd("nanoshell> ", 0);
	str = get_next_line(0, 0);
	while (1)
	{
		if (!str)
			break;
		tab = first_split(str);
		if (!tab)
		{
			free(str);
			break;
		}
		if (syntax_error(tab))
			return (0);
		lst = generator(tab);
		head = lst;
		tokenisation(&lst);
		print_lst(head);
		free_tab(tab, i);
		free(str);
		ft_putstr_fd("nanoshell> ", 0);
		str = get_next_line(0, 0);
	}
	get_next_line(0, 1);
	// tokenisation(&lst);
	// print_lst(lst);
}