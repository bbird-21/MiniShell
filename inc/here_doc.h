/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:39:14 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/04/21 00:58:23 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_H
# define HERE_DOC_H

# include "minishell.h"

void	here_doc(t_list **list, t_list *tmp, t_cmd *cmd);
void	opening(t_list **cmd);
int		do_here_doc(t_list **lst, char *limiter);

#endif
