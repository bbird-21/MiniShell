/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:28:38 by alvina            #+#    #+#             */
/*   Updated: 2023/04/13 14:01:38 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*state_00(char *str)
{
	return (expansion(str));
}

char	*state_01(char *str)
{
	char	*new;

	new = remove_quotes(str);
	if (g_g.exit_malloc)
		return (NULL);
	magic_space(new);
	free(str);
	return (new);
}

char	*state_02(char *str)
{
	char	*new;
	char	*new2;

	new = remove_quotes(str);
	if (g_g.exit_malloc)
		return (NULL);
	new2 = expansion(new);
	magic_space(new2);
	free(str);
	return (new2);
}

t_fp_exp	handling_table(unsigned char state)
{
	static t_fp_exp	table[3] = {
		state_00,
		state_01,
		state_02
	};

	return (table[state]);
}

char	*do_job(char *str, int type)
{
	t_fp_exp	fp;

	if (type == 1)
		return (str);
	if (str)
		fp = handling_table(get_state(str[0]));
	else
		return (NULL);
	return (fp(str));
}
