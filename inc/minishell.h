/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 09:53:47 by alvina            #+#    #+#             */
/*   Updated: 2023/03/29 11:13:18 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*	GNU C Library  */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>

/*	Personal Library  */
# include "utils.h"
# include "tools.h"
# include "lst.h"
# include "env.h"
# include "expansion.h"
# include "clean.h"
# include "builtins.h"
# include "here_doc.h"
# include "exec.h"
# include "parsing.h"

/*	Declaration of the global variable required to manage the
	exit_status code  */
extern int g_exit_status;

/*	The main program  */
void		minishell(char *str, char **env);

/*	Required to create the token  */
int			is_space(char *str);
int			is_red(char *str);
int			is_pipe(char *str);
int			is_separator(char *str);
int			changing_state(char c);
int			count_words(char *str, int i);
void		first_split(char *str);

/*	Required to generate token  */
t_token		*create_token(char *str);
void		token_generator(char **tab, int i);

/*	Tokenisation  */
int			what_red(char *str);
void		tokenisation(t_list **lst);

/*  Parse error	*/
int		parse_quote(char *str);
int		error_msg(char *value);
int		parse_pipe(t_list *previous, t_token *curr_data, t_list *next);
int		parse_red(t_token *curr_data, t_list *next);
int		parse_error(t_list *lst);

/*	Error management  */
void		free_exit(char *error);
void		cleaning_tkn(char **tab, t_list *lst);

/*	T_cmd creation	*/
t_list		*arg_red_list(t_list **arg_red, int type, char *str);
t_cmd		*data_cmd(t_list *token, int *flag);
void		cmd_generator(t_list **token);

#endif