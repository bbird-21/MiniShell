/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 20:40:11 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/04/11 19:12:17 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

char 		*remove_quotes(char *str);
void		split_state(t_list	**list);
char		*get_token(char *str, int *k, int type);
char		**ft_split(char *s, char c);
void		magic_space(char *str);
int			get_var_size(char *str);

int			get_exp_size(char *env_var);
int			get_var_size(char *str);
int			set_var(char *str, char **sh_var, char **sign_var);
char		*expansion(char *token);

void    	tokjoin(t_list **list, int j);
void		join_token(t_list **list, char *new);

char		*state_00(char *str);
char		*state_01(char *str);
char		*state_02(char *str);
t_fp_exp	handling_table(unsigned char state);
char		*do_job(char *str, int type);

int			ft_strrlen(const char *str);
bool		new_state(char c, int state);

#endif