/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:04:12 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/18 19:12:12 by alvina           ###   ########.fr       */
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
char	*get_bin(char *cmd);
char	**get_path(char **env);
char	*get_bin_path(char *cmd, char **path);
char	**get_bin_args(char *cmd, char *bin);

/*	Extra functions required for norminette  */
char	**extra_bin_args(char *cmd, char *bin, int i);
void	extra_launcher(t_data *data, int i);
void	extra_init(t_data *data);
void	extra_loop_free(t_storage_cmd *node);
void	loop_job(t_storage_cmd *st_cmd);
void	cmd_not_found(t_storage_cmd *node);


/*	Init and launch pipex	*/
void	init_data_list(t_data *data);
void	init(int argc, char **argv, char **env, t_data *data);
void	pipex(t_list **cmd);
void	dup_and_exe(t_storage_cmd *st_cmd);
void	fill_data_bin(t_storage_cmd *st_cmd, t_cmd *cmd);

void	close_fds(t_storage_cmd *st_cmd);
char	*ft_strjoin_path(char *line, char *buffer);
char	*ft_strnchr(char *s1, char *s2, size_t len);

/*	Exec of the built-ins	*/
ptr_fun	funct(int flag);
void    execve_builtin(int flag, char **arg);
int is_builtin(char *str, int pipe);

#endif