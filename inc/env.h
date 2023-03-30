/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:25:50 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/30 10:26:29 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

/*  Environnement management    */
t_list		*handler(int swtch, char **env, char *arg);
pf	        fct(int swtch);

/*  Environnement functions */
void	getting(t_list **envp, char **env, char *arg);
void	cleaning(t_list **envp, char **env, char *arg);
void	creating(t_list **envp, char **env, char *arg);
void	appending(t_list **envp, char **env, char *arg);
void	adding(t_list **envp, char **env, char *arg);
void	deleting(t_list **envp, char **env, char *arg);
void	modifying(t_list **envp, char **env, char *arg);

/*  Utils   */
char		*ft_getenv(char *name);
char		*ft_key(char *str);
char		*ft_value(char *str);
t_env	    *create_env(char *str);
char	    *joining_value(t_env *data, char *value);

#endif