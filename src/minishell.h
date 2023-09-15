/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaragoz <mkaragoz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:02:54 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/09/15 18:26:32 by mkaragoz         ###   ########.fr       */
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
	int set_path;
	int is_builtin;
	char ***av;
	int **av_token;
	int pipe_count;
} t_exec;


typedef struct s_env
{
	char	*content;
	struct s_env	*next;
} t_env;

typedef struct s_tools
{
	int quote_mode;
	bool arg_mode;
	bool double_redirection;
} t_tools;

struct s_vars
{
	t_env	*env_list;
	t_env	*env_head;
	t_env	*env_tail;
	int stdo;
	int stdi;
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

void ms_set_execve_arg(void);
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
int ms_exec(int sentence);
int ms_print_env(char **env);
int ms_set_path(char **env);
void ms_run_env(void);
char *ms_test_path(char *cmd);
void ms_free_tokens(void);
void ms_set_arg_false(int i);
void ms_check_env(t_token *org_token);
void ms_put_env(t_token *token, int *i);
int ms_node_check_redirection(char *content);
int ms_node_check_builtin(char *content);
char *ms_get_env(char *s);
t_env *ms_new_env(char *content);
void ms_set_envlist(char **env);
void ms_run_export(char *s);

#endif
