/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:31:30 by ale-sain          #+#    #+#             */
/*   Updated: 2023/03/18 19:15:57 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
#define BUILTINS_H

void	pwd(char **arg);
void	export(char **arg);
void	unset(char **arg);
void    ft_env(char **arg);
void    cd(char **arg);
void	echo(char **arg);
void    ft_exit(char **arg);


#endif