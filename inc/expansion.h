/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 20:40:11 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/31 11:01:55 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

char 	*remove_quotes(char *str);
char	*do_job(char *str);
void	split_state(t_list	**list);
char	*get_token(char *str, int *k);
char	**ft_split(char *s, char c);
void	magic_space(char *str);
int	get_var_size(char *str);

int	    add_node_back_token(t_list **l, char *str, int *index, int type);
int		get_exp_size(char *env_var);
int		get_var_size(char *str);
int		set_var(char *str, char **sh_var, char **sign_var);
char	*expansion(char *token);

int     tokjoin(t_list **list, int j);
int	    split_token(t_list **list, char *new);

char	*state_00(char *str);
char	*state_01(char *str);
char	*state_02(char *str);
t_fp_exp	handling_table(unsigned char state);
char	*do_job(char *str);

int	ft_strrlen(const char *str);
bool	new_state(char c, int state);

#endif