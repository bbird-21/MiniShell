/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 09:53:47 by alvina            #+#    #+#             */
/*   Updated: 2023/03/29 13:06:44 by ale-sain         ###   ########.fr       */
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


#endif