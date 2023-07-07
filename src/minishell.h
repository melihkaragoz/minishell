/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaragoz <mkaragoz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:02:54 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/07/08 01:36:03 by mkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>

struct s_vars
{
	char	*line;
	char	*cmd;
	char	**paths;
	char	*v_path;
} g_vars;

typedef struct s_line
{
	char	*cmd;
	char	**params;
	char	*line;
} t_line;


int		ms_strlen(char *s);
char	*ms_get_cmd(void);
int		ms_exec(void);
int		ms_print_env(char **env);
int		ms_set_path(char **env);
char	*ms_test_path(char *cmd);
void	ms_free_struct(void);
#endif
