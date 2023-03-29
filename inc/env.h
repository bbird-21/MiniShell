/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:25:50 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/29 11:02:01 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

t_list		*handler(int swtch, char **env, char *arg);
char		*ft_getenv(char *name);
char		*ft_key(char *str);
char		*ft_value(char *str);

#endif