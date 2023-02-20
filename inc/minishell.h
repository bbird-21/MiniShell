/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 09:53:47 by alvina            #+#    #+#             */
/*   Updated: 2023/02/20 22:41:05 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>

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
} t_type;

typedef struct s_token
{
	char            *value;
    int             type;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	t_token 		*arg;
	t_token 		*red;
	int				infile;
	int				outfile;
	struct s_cmd	*next;
} t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef void (*pf)(t_env **, char **, char *);

//		UTILS
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
int		ft_strlen(char *str);
t_token	*token_add_back(t_token **lst, t_token *new);
t_cmd	*cmd_add_back(t_cmd **lst, t_cmd *new);
t_env	*env_add_back(t_env **lst, t_env *new);
t_token	*token_last(t_token *lst);
t_cmd	*cmd_last(t_cmd *cmd);
t_env	*env_last(t_env *cmd);
char	*ft_strnstr(char *big, char *little, int len);
char	*ft_strdup(char *s);
char	*ft_strnstr(char *big, char *little, int len);
char	*join(char *s1, char *s2);

//		INUTILS
void	print_cmd(t_cmd *cmd);;
void	print_lst(t_token *lst);
void	print_env(t_env *lst);

//		TRASHING
void	ft_lstdelone(t_token *lst);
void	ft_lstclear(t_token **list);
char	**free_tab(char **tab, int j);
void	ft_cmdclear(t_cmd **lst);

//		MAIN
void	minishell(char *str);

//------------TOKEN_CREATION-----------
//			split
int		is_space(char *str);
int		is_red(char *str);
int		is_pipe(char *str);
int 	is_separator(char *str);
int		changing_state(char c, int state);
int		count_words(char *str);
char	**first_split(char *str);
char	**splitting(char **tab, char *str, int state);
int		wording_other(char *str, char ***tab, int j, int *state);
int    	wording_sep(char *str, char ***tab, int j, int (*f)(char *));
int		length(char *str, int *state);
//			token_generator
void	*new_token(t_token **lst, char *str);
t_token	*create_token(char *str);
t_token	*token_generator(char **tab);


//----------TOKENISATION------------
int		what_red(char *str);
void	tokenisation(t_token **lst);

//-----------PARSE ERROR-----------
int		parse_quote(char *str);
int		error_msg(char *value);
int		parse_pipe(t_token *previous, t_token *curr, t_token *next);
int		parse_red(t_token *curr, t_token *next);
int		parse_error(t_token *lst);


//-----------HANDLING_ENVIRONNEMENT-----------
t_env	*handler(int swtch, char **env, char *arg);

//------------CMD_CREATION-------------
void	cmd_arg(t_token **arg, char *str);
void    cmd_red(t_token **red, int type, char *file);
int		new_cmd(t_cmd **cmd, t_token **list);
void    cmd_generator(t_token **lst);

#endif