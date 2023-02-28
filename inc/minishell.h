/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 09:53:47 by alvina            #+#    #+#             */
/*   Updated: 2023/02/28 15:58:48 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PATH_MAX 4096

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

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_token
{
	char            *value;
    int             type;
}	t_token;

typedef struct s_cmd
{
	t_list 		*arg;
	t_list 		*red;
	int				infile;
	int				outfile;
} t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
}	t_env;

typedef void (*pf)(t_list **, char **, char *);

//		UTILS
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
int		ft_strlen(char *str);
char	*ft_strdup(char *s);
int		ft_strncmp(char *s1, char *s2, int n);
char	*join(char *s1, char *s2);
char	*ft_strnstr(char *big, char *little, int len);
int		ft_strchr(char *str, char c);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
char	*simple_join(char *s1, char *s2);

//		LST UTILES
t_list	*ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);

//		INUTILS
void	print_env(void *content);
void	print_token(void *content);
void	print_cmd(void *content);
void	print_lst(t_list *lst, void (*print)(void *));

//		TRASHING
void	token_cleaner(void *content);
void	env_cleaner(void *content);
void	cmd_cleaner(void *content);
void	ft_lstclear(t_list **lst, void (*del)(void *));
char	**free_tab(char **tab, int j);

//		MAIN
void	minishell(char *str);

//------------TOKEN_CREATION-----------
//			split
int		is_space(char *str);
int		is_red(char *str);
int		is_pipe(char *str);
int 	is_separator(char *str);
int		changing_state(char c);
int		count_words(char *str);
void	first_split(char *str);

//			token_generator
t_token	*create_token(char *str);
void	token_generator(char **tab);


//----------TOKENISATION------------
int		what_red(char *str);
void	tokenisation(t_list **lst);

//-----------PARSE ERROR-----------
int		parse_quote(char *str);
int		error_msg(char *value);
int		parse_pipe(t_list *previous, t_token *curr_data, t_list *next);
int		parse_red(t_token *curr_data, t_list *next);
int		parse_error(t_list *lst);

//-----------HANDLING_ENVIRONNEMENT-----------
t_list	*handler(int swtch, char **env, char *arg);
char	*ft_getenv(char *name);
char	*ft_key(char *str);
char	*ft_value(char *str);

//------------CMD_CREATION-------------
t_list	*arg_list(t_list **arg, char *str);
t_list	*red_list(t_list **red, int type, char *file);
t_cmd	*data_cmd(t_list *token, int *flag);
void	cmd_generator(t_list **token);

//------------BUILT-INS------------
void	pwd(void);
void	export(char *name);
void	unset(char *key);
void    ft_env(void);
void    cd(char *arg);
void	echo(char **tab);

void	expansion(t_list *token_lst);
void    exec(t_list *cmd_lst);

#endif