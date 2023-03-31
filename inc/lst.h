/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:18:27 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/31 12:49:50 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_H
# define LST_H

# include "tools.h"

t_list		*ft_lstadd_back(t_list **lst, t_list *new);
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstnew(void *content);


int		add_node_back_token(t_list **l, char *str, int *index, int type);
void		print_lst(t_list *lst, void (*print)(void *));
void		print_token(void *content);
void		print_env(void *content);
void		print_cmd(void *content);

char		*trans_env(void *content);
char		*trans_token(void *content);
char		**translator(t_list *lst, char *(translate)(void *));


#endif