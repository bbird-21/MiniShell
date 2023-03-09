/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:18:27 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/09 09:50:05 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_H
# define LST_H

# include "tools.h"

t_list	*ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);

void		get_dblist(void (*fp)(t_dblist *), t_dblist **dblist);
void		init_list(t_dblist *dblist);

void		add_node_back_env(t_dblist *l, char *key, char *value);
void		add_node_back_token(t_list **l, char *str, int *index, int type);
void		print_lst(t_list *lst, void (*print)(void *));
void		print_token(void *content);
void		print_env(void *content);
void		print_cmd(void *content);

char	*trans_env(void *content);
char	*trans_token(void *content);
char	**translator(t_list *lst, char *(translate)(void *));
// void	*new_token(t_token **lst, char *str);
// t_token	*ft_lstadd_back(t_token **lst, t_token *new);
// t_token	*ft_lstnew(char *str);
// t_token	*ft_lstlast(t_token *lst);

#endif