/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:02:54 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/10/08 17:10:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libft/libft.h"
#include "../get_next_line/get_next_line.h"
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>

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
	int	arg_num;
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

typedef struct s_return_red
{
	int index;
	int type;
} t_return_red;

struct s_vars
{
	t_return_red **retred;
	t_env	*env_list;
	t_env	*env_head;
	t_env	*env_tail;
	t_env	*export_list;
	t_env	*export_head;
	t_env	*export_tail;
	t_exec *exec;
	t_token *tmp_token;
	t_token *f_token;
	t_token *head;
	t_token *tokens;
	int	exit_status;
	int stdo;
	int stdi;
	int i;
	int j;
	char *line;
	char **paths;
	char *v_path;
	char **env;
	t_tools *p_tools;
	int	rm;
	char *prompt;
	int		quit_flag;
} g_vars;

typedef struct s_line
{
	char *cmd;
	char **params;
	char *line;
} t_line;


t_return_red **ms_isred_sentence(int sentence);
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
char *ms_getenv(char *s); // bagli listeden cekiyor
// char *ms_get_env(char *s);
t_env *ms_new_env(void);
void ms_set_envlist(char **env);
void ms_run_export(char *s);
void ms_put_dollar(t_token *token, int *i);
void	ms_copy_struct(t_env *s);
void ms_exec_builtin(char **sentence);
void ms_print_export(void);
t_env	*ms_lstchr(char *s);
void	ms_update_env_tail(void);
int	ms_strncmp(char *a ,char *b, char c);
void ms_run_unset(char *s);
void ms_toggle_signal(int get);
void	ms_exit(char *msg, int stat);
int	ms_free(char *s);
int	ms_free_db_array(char **db);
void ms_add_env_list(char *s);
int ms_redirect_manage(int sentence, int type, int index);
void ms_remove_redrets(int sentence, int index);
int	ms_check_executable(void);
int ms_redirect_parse(char **sentence, int index);
void ms_prepare_tokens(void);
int ms_set_infile(char **pt, int index);
int ms_set_outfile(char **pt, int index, int mod);
void ms_set_heredoc(char **pt, int index);
void ms_signal_helper(int get);
void ms_put_status(t_token *token, int *i);
void ms_put_program_name(t_token *token, int *i);
#endif
