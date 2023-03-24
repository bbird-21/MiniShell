/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 22:02:38 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/24 11:02:50 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	The string will be split at each change of state.
	A new_dblist containing splited token is created and
	the old_dblist point to the new_dblist .
*/

static bool	new_state(char c, int state)
{
	if (state == NONE)
	{
		if (c == '\'' || c == '"')
			return (true);
	}
	if (state == SP_QUOTES)
	{
		if (c == '\'')
			return (true);
	}
	if (state == DB_QUOTES)
	{
		if (c == '"')
			return (true);
	}
	return (false);
}

int	get_state(char c)
{
	if (c == '\'')
		return (SP_QUOTES);
	else if (c == '"')
		return (DB_QUOTES);
	return (NONE);
}

static int	countwords(char *str)
{
	int		index;
	int		word;
	int		state;
	
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

char	*get_token(char *str, int *k)
{
	char			*dup;
	int				j;
	int				state;

	state = get_state(str[*k]);
	j = 0;
	dup = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!dup)
		return (NULL);
	while (str[*k])
	{
		dup[j] = str[*k];
		j++;
		(*k)++;
		if (new_state(str[*k], state))
		{
			if (!state)
				break ;
			dup[j] = str[*k];
			j++;
			(*k)++;
			break ;
		}
	}
	// if (ft_strlen(dup) == 1 && dup[j - 1] == '$' && countwords(str) != 1)
	// 	return (do_job(NULL));
	dup[j] = '\0';
	return (do_job(dup));
}

void	split_state(t_list	**l)
{
	static int	index = 0;
	t_list		*new_list;
	t_list		*subdivide_token;
	t_list		*tmp;
	t_token 	*data;
	int			j;

	subdivide_token = NULL;
	new_list = NULL;
	tmp = (*l);
	while (tmp)
	{
		data = (t_token *)(tmp->content);
		j = 0;
		while (j < countwords(data->value))
		{
			add_node_back_token(&subdivide_token, data->value, &index, data->type);
			j++;
		}
		if (j > 1)
			tokjoin(&subdivide_token);
		ft_lstadd_back(&new_list, subdivide_token);
		subdivide_token = NULL;
		tmp = tmp->next;
		index = 0;
	}
	ft_lstclear(&subdivide_token, token_cleaner);
	ft_lstclear(l, token_cleaner);
	// print_lst(new_list, print_token);
	return (cmd_generator(&new_list));
}
