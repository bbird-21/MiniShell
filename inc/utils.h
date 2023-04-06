/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:09:54 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/04/06 15:14:00 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "exec.h"

int		ft_strlen(char *str);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strnstr(char *big, char *little, int len);
bool	ft_strcmp(const char *s1, const char *s2);
int		get_state(char c);
int		ft_isalnum(int c);

void	ft_putendl_fd(char *s, int fd);
char	*ft_strdup(char *s);
int		ft_strncmp(char *s1, char *s2, int n);
char	*join(char *s1, char *s2);
int		ft_strchr(char *str, char c);
int		ft_isalpha(int c);
char	*simple_join(char *s1, char *s2);

char	*ft_strjoin(char *line, char *buffer);
char	*get_next_line(int fd);

/*	These lines belows are required by <utils_pipex_02.c>  */
void	ft_out(int *status);
void	empty_data(t_storage_cmd *cmd);
void	clean_data(t_storage_cmd *cmd);
void	mini_gc(t_list *cmd, t_storage_cmd *st);
void	closing_cmd(t_list *cmd);

#endif