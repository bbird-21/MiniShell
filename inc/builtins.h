/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:31:30 by ale-sain          #+#    #+#             */
/*   Updated: 2023/04/24 19:51:19 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

void	pwd(char **arg);
void	export(char **arg);
void	unset(char **arg);
void	ft_env(char **arg);
void	cd(char **arg);
void	echo(char **arg);
void	ft_exit(char **arg);
char	*home_prt(void);
void	closing_job(t_storage_cmd *st_cmd, int flag);

#endif