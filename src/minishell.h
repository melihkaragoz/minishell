/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaragoz <mkaragoz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:02:54 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/08/30 23:40:44 by mkaragoz         ###   ########.fr       */
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


typedef struct s_token
{
	char	*content;
	int		type;
	struct s_token	*next;
}				t_token;

// typedef struct s_exec
// {
// 	char	**str;
// 	t_exec	*next;
// }				t_exec;

struct s_vars
{
	int		i;
	int		j;
	t_token	*f_token;
	t_token	*tokens;
	char	*line;
	char	**paths;
	char	*v_path;
	char	**env;
} g_vars;


typedef struct s_line
{
	char	*cmd;
	char	**params;
	char	*line;
} t_line;


int		ms_strlen(char *s);
void	ms_init_token(void);
t_token	*ms_new_token(void);
void	ms_set_tokens(void);
void	ms_print_tokens(void);
int		ms_check_schars(int	j);
int		ms_cmp(int i, char c);
int		ms_exec(void);
int		ms_print_env(char **env);
int		ms_set_path(char **env);
char	*ms_test_path(char *cmd);
void	ms_free_tokens(void);
#endif
