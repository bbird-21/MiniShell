/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:31:30 by ale-sain          #+#    #+#             */
/*   Updated: 2023/03/30 17:28:53 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
#define BUILTINS_H

/*	Functions	*/
void	pwd(char **arg);
void	export(char **arg);
void	unset(char **arg);
void    ft_env(char **arg);
void    cd(char **arg);
void	echo(char **arg);
void    ft_exit(char **arg);

/*	Utils	*/
void	return_code(int code);


#endif