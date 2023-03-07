/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:25:50 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/07 19:40:36 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

char 	*remove_quotes(char *str);
char	*do_job(char *str);
void	split_state(t_list	**list);
char	*get_token(char *str, int *k);
char	**ft_split(char const *s, char c);
void	magic_space(char *str);
void	init_env(t_dblist *dblist, char **env);

int		parse_quote(char *str);
int		error_msg(char *value);
int		parse_pipe(t_list *previous, t_token *curr_data, t_list *next);
int		parse_red(t_token *curr_data, t_list *next);
int		parse_error(t_list *lst);

#endif