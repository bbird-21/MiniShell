/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 20:40:11 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/04/24 19:55:01 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

char		*remove_quotes(char *str);
void		split_state(t_list	**list);
char		*get_token(char *str, int *k, int type);
char		**ft_split(char *s, char c);
void		magic_space(char *str);
int			get_var_size(char *str);

int			tokjoin(t_list **list, int j);

int			get_exp_size(char *env_var);
int			get_var_size(char *str);
int			set_var(char *str, char **sh_var, char **sign_var);
char		*expansion(char *token);

void		join_token(t_list **list, char *new);

char		*state_00(char *str);
char		*state_01(char *str);
char		*state_02(char *str);
t_fp_exp	handling_table(unsigned char state);
char		*do_job(char *str, int type);
void		looping(t_list **list);
int			ft_strrlen(const char *str);
bool		new_state(char c, int state);
char		*ft_itoa(int n);
char		*set_expansion(char *token, char **new, int i, int k);

#endif
