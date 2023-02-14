/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 09:53:47 by alvina            #+#    #+#             */
/*   Updated: 2023/02/14 18:37:13 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
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

//		UTILS
void	ft_putstr_fd(char *s, int fd);
int		ft_strlen(char *str);
t_token	*ft_lstadd_back(t_token **lst, t_token *new);
t_token	*ft_lstnew(char *str);
t_token	*ft_lstlast(t_token *lst);
char	*ft_strnstr(char *big, char *little, int len);

//		INUTILS
void	print_lst(t_token *lst);

//		TRASHING
void	ft_lstclear(t_token **list);
char	**free_tab(char **tab, int j);

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
void	*generator_token(t_token **lst, char *str);
t_token	*generator(char **tab);

//----------TOKENISATION------------
int		what_red(char *str);
void	tokenisation(t_token **lst);

//-----------EXPANSION-----------

#endif