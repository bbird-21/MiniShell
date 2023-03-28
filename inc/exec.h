/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:04:12 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/28 13:11:01 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "tools.h"

/* The open() system call requires these preprocessor directives  */
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdint.h>
# include <stdbool.h>

/*	Definition of structures required by pipex  */
typedef enum e_sig_err {
	ERR_OPEN,
	ERR_ARG,
	ERR_EXIST,
	ERR_EXE,
	ERR_FORK,
	ERR_PIPE,
	ERR_MEM,
	ERR_ENV,
	ERR_PATH,
	ERR__LENGHT
}	t_sig_err;

typedef struct s_error
{
	int		sig_err;
	char	*sig_msg;
}			t_error;

/*	Prototypes required by <get.c>  */
char	**get_path(char **env);
char	*get_bin_path(char *cmd, char **path);

/*	Extra functions required for norminette  */
void	loop_job(t_storage_cmd *st_cmd, t_list *cmd);
void	cmd_not_found(t_storage_cmd *node, t_list *cmd);


/*	Init and launch pipex	*/
void	pipex(t_list **cmd);
void	dup_and_exe(t_storage_cmd *st_cmd, t_list *cmd);
void	fill_data_bin(t_storage_cmd *st_cmd, t_cmd *cmd);

void	close_fds(t_storage_cmd *st_cmd);
char	*ft_strjoin_path(char *line, char *buffer);
char	*ft_strnchr(char *s1, char *s2, size_t len);

/*	Exec of the built-ins	*/
ptr_fun	funct(int flag);
void    execve_builtin(int flag, char **arg);
int is_builtin(char *str, int pipe);
int check_arg(char **arg, int max, char *fct);

/*	signals 	*/
int	ft_state(int state);
void	sig_handler(int signum);

void	mini_gc(t_list *cmd, t_storage_cmd *st);
void	clean_data(t_storage_cmd *cmd);
void	empty_data(t_storage_cmd *cmd);

/*	Required by <dup.>  */
void	dup_and_exe(t_storage_cmd *st_cmd, t_list *cmd);
void	dupping(t_storage_cmd *st_cmd);
void	protecting(t_storage_cmd *st_cmd, t_list *cmd);

#endif