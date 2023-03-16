/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:11:41 by ale-sain          #+#    #+#             */
/*   Updated: 2023/03/16 00:20:01 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEAN_H
# define CLEAN_H

void	token_cleaner(void *content);
void	env_cleaner(void *content);
void	cmd_cleaner(void *content);
void	ft_lstclear(t_list **lst, void (*del)(void *));
char	**free_tab(char **tab, int j);

#endif