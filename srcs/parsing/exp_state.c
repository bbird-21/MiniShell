/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:28:38 by alvina            #+#    #+#             */
/*   Updated: 2023/04/17 16:53:37 by alvina           ###   ########.fr       */
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
		exit(12);
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
		exit(12);
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
