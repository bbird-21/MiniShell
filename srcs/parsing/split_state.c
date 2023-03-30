/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 22:02:38 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/30 15:44:52 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	The string will be split at each change of state.
	A new_dblist containing splited token is created and
	the old_dblist point to the new_dblist .
*/

static int	countwords(char *str)
{
	int	index;
	int	word;
	int	state;

	word = 0;
	index = 0;
	state = get_state(str[index]);
	index++;
	while (str[index])
	{
		if (new_state(str[index], state))
		{
			word++;
			if (state && str[index + 1] != 0)
				index++;
			state = get_state(str[index]);
		}
		index++;
	}
	if (state == NONE)
		word++;
	return (word);
}

static void	making_token(char *str, int *k, int state, char **dup)
{
	int	j;

	j = 0;
	while (str[*k])
	{
		(*dup)[j] = str[*k];
		j++;
		(*k)++;
		if (new_state(str[*k], state))
		{
			if (!state)
				break ;
			(*dup)[j] = str[*k];
			j++;
			(*k)++;
			break ;
		}
	}
	(*dup)[j] = 0;
}

char	*get_token(char *str, int *k, int type)
{
	char	*dup;
	int		state;

	state = get_state(str[*k]);
	dup = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!dup)
		return (NULL);
	making_token(str, k, state, &dup);
	if (ft_strlen(dup) == 1 && dup[0] == '$' && countwords(str) != 1)
		return (free(dup), NULL);
	return (do_job(dup, type));
}

void	dividing(t_list **subdivide_token, t_list *tmp, int *index)
{
	int		j;
	t_token	*data;

	data = (t_token *)(tmp->content);
	j = 0;
	while (j < countwords(data->value))
	{
		add_node_back_token(subdivide_token, data->value, index, data->type);
		j++;
	}
	tokjoin(subdivide_token, j);
}

void	split_state(t_list **l)
{
	static int	index;
	t_list		*new_list;
	t_list		*subdivide_token;
	t_list		*tmp;

	index = 0;
	subdivide_token = NULL;
	new_list = NULL;
	tmp = (*l);
	while (tmp)
	{
		dividing(&subdivide_token, tmp, &index);
		ft_lstadd_back(&new_list, subdivide_token);
		subdivide_token = NULL;
		tmp = tmp->next;
		index = 0;
	}
	ft_lstclear(&subdivide_token, token_cleaner);
	ft_lstclear(l, token_cleaner);
	return (cmd_generator(&new_list, -1));
}
