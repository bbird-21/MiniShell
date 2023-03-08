/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:12:42 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/08 19:55:14 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# define EXPAND 36

typedef enum e_env_setting{
	CREATING,
	DELETING,
	ADDING,
	MODIFYING, 
	CLEANING,
	GETTING,
	APPENDING
}	t_env_setting;

extern int g_exit_status;

typedef char * (*t_fp_exp)(char *str);

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

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;


typedef	struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

typedef struct s_dblist
{
	t_token			*first;
	t_token			*last;
	t_env			*first_env;
	t_env			*prev_env;
}					t_dblist;

typedef struct s_list
{
	void			*content;
	int				pfd[2];
	struct s_list	*next;
}					t_list;

typedef void (*pf)(t_list **, char **, char *);

typedef struct s_cmd
{
	t_list 		*arg;
	t_list 		*red;
	int			infile;
	int			outfile;
}				t_cmd;

typedef struct s_gc
{
	void			*addr;
	struct	s_gc	*next;
}					t_gc;

typedef struct s_llptr
{
	t_token			*token;
	t_cmd			*cmd;
}					t_llptr;

typedef enum e_state
{
	NONE,
	SP_QUOTES,
	DB_QUOTES
}	t_state;

#endif