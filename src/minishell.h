/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anargul <anargul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:02:54 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/09/09 17:30:08 by anargul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libft/libft.h"
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <stdbool.h>

typedef struct s_token
{
	char *content;
	int type;
	struct s_token *next;
} t_token;

// typedef struct s_exec
// {
// 	char	**str;
// 	t_exec	*next;
// }				t_exec;

typedef struct s_exec
{
	// int		*pipe_idx;
	char	**av;
	int		pipe_count;
	bool builtin;
}		t_exec;

typedef struct s_tools
{
	int quote_mode;
	bool arg_mode;
	bool double_redirection;
} t_tools;

struct s_vars
{
	int i;
	int j;
	t_exec *exec;
	t_token *tmp_token;
	t_token *f_token;
	t_token *head;
	t_token *tokens;
	char *line;
	char **paths;
	char *v_path;
	char **env;
	t_tools *p_tools;
} g_vars;

typedef struct s_line
{
	char *cmd;
	char **params;
	char *line;
} t_line;

int	ms_exec(void);
void ms_set_nodes(void);
int ms_strlen(char *s);
void ms_init(void);
void ms_make_nodes(void);
void ms_set_tokens(void);
void ms_print_tokens(void);
t_token *ms_new_token(void);
int ms_end_of_word(void);
void ms_set_quote_mode(int set);
int ms_check_seperators(char *s);
int ms_cmp(int i, char c);
int ms_exec(void);
int ms_print_env(char **env);
int ms_set_path(char **env);
char *ms_test_path(char *cmd);
void ms_free_tokens(void);
void ms_set_arg_false(int i);
void ms_check_env(t_token *org_token);
void ms_put_env(t_token *token, int *i);
#endif
