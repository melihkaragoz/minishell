/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaragoz <mkaragoz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:02:54 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/07/07 22:39:36 by mkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>

struct s_vars
{
	char	**paths;
} g_vars;

typedef struct s_line
{
	char	*cmd;
	char	**params;
	char	*line;
} t_line;


int		ms_strlen(char *s);
void	ms_prepare_input(t_line *tl);
char	*ms_prepare_cmd(t_line *tl);
char	**ms_prepare_params(t_line *tl);
int		ms_exec(t_line *tl);
int		ms_print_env(char **env);
int		ms_set_path(char **env);
#endif
