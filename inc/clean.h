/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:11:41 by ale-sain          #+#    #+#             */
/*   Updated: 2023/04/12 17:32:09 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEAN_H
# define CLEAN_H

void	token_cleaner(void *content);
void	env_cleaner(void *content);
void	cmd_cleaner(void *content);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	free_tab(char **tab, int j);
void	exit_malloc(void);
void	return_code(int code);
void	extra_free_tab(char ***tab);

#endif