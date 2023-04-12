/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:12:42 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/04/12 19:49:20 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# define EXPAND 36

# include <aio.h>

typedef enum e_env_setting{
	CREATING,
	DELETING,
	ADDING,
	MODIFYING,
	CLEANING,
	GETTING,
	APPENDING
}	t_env_setting;

typedef struct s_globale
{
	int	exit_status;
	int	exit_malloc;
	int	exit_here_doc;
}				t_globale;

extern t_globale	g;

typedef char *	(*t_fp_exp)(char *str);

typedef enum e_type
{
	WORD,
	FD,
	LIM,
	RIN,
	ROUT,
	DRIN,
	DROUT,
	PIPE
}	t_type;

typedef enum e_handle_sig
{
	READLINE,
	PIPEX,
	HERE_DOC
}	t_handle_sig;

typedef struct s_token
{
	char	*value;
	int		type;
}					t_token;

typedef struct	s_env
{
	char			*key;
	char			*value;
}					t_env;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef void	(*pf)(t_list **, char **, char *);
typedef void	(*ptr_fun)(char **);

typedef struct s_cmd
{
	t_list		*arg;
	t_list		*red;
	int			pfd[2];
	int			infile;
	int			outfile;
}				t_cmd;

typedef enum e_state
{
	NONE,
	SP_QUOTES,
	DB_QUOTES
}	t_state;

/*	Required by Pipex to create the new double linked list
	that contains all data about binaries.
 */
typedef struct s_storage_cmd
{
	char					**bin_args;
	char					*bin_path;
	char					**env;
	int						nb_cmd;
	int						pos;
	int						pfd[2];
	int						fd_tmp;
	int						fd_in;
	int						fd_out;
	int						ok;
	int						toclose;
	pid_t					*pid;
}							t_storage_cmd;

typedef struct s_dblist
{
	t_storage_cmd	*first;
	t_storage_cmd	*last;
}					t_dblist;

// typedef struct s_data
// {
// 	int				pfd[2];
// 	int				fd_in;
// 	int				fd[2];
// 	pid_t			*pid;
// 	t_dblist		dblist;
// 	t_args			args;
// }					t_data;
/*	End of Pipex prerequisites  */

#endif