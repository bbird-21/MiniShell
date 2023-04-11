/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:03:38 by ale-sain          #+#    #+#             */
/*   Updated: 2023/03/31 12:45:45 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifndef PARSING_H
# define PARSING_H

/*	Required to create the token  */
int			is_space(char *str);
int			is_red(char *str);
int			is_pipe(char *str);
int			is_separator(char *str);
int			changing_state(char c);
int         length(char *str);
int			count_words(char *str, int i);
void		first_split(char *str);

/*	Required to generate token  */
t_token		*create_token(char *str);
void		token_generator(char **tab, int i);

/*	Tokenisation  */
int			what_red(char *str);
void		tokenisation(t_list **lst);

/*  Parse error	*/
int		parse_quote(char *str);
int		error_msg(char *value);
int		parse_pipe(t_list *previous, t_token *curr_data, t_list *next);
int		parse_red(t_token *curr_data, t_list *next);
int		parse_error(t_list *lst);

/*	Error management  */
void		free_exit(char *error);
void		cleaning_tkn(char **tab, t_list *lst);

/*	T_cmd creation	*/
t_list		*arg_red_list(t_list **arg_red, int type, char *str);
t_cmd		*data_cmd(t_list *token, int *flag);
void	    cmd_generator(t_list **token, int i);
void	    reverse_magic_space(t_list **arg);
void	    cleaning_cmd(t_cmd *data, t_list **token, t_list **cmd);

#endif