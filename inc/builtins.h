/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:31:30 by ale-sain          #+#    #+#             */
/*   Updated: 2023/02/28 20:32:07 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
#define BUILTINS_H

void	pwd(void);
void	export(char *name);
void	unset(char *key);
void    ft_env(void);
void    cd(char *arg);
void	echo(char **tab);
void    ft_exit(char *str);


#endif