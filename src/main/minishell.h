/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anargul <anargul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:02:54 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/10/14 10:51:32 by anargul          ###   ########.fr       */
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

typedef struct s_gc
{
	void *content;
	struct s_gc *next;
} t_gc;

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
	int red_count;
	int arg_num;
} t_exec;

typedef struct s_env
{
	char *content;
	struct s_env *next;
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

typedef struct s_heredoc_kw
{
	char *keyword;
	char **str;
	struct s_heredoc_kw *next;
} t_heredoc_kw;

typedef struct s_heredoc_str
{
	char *str;
	struct s_heredoc_str *next;
} t_heredoc_str;

struct s_vars
{
	t_return_red **retred;
	t_env *env_list;
	t_env *env_head;
	t_env *env_tail;
	t_env *export_list;
	t_env *export_head;
	t_env *export_tail;
	t_exec *exec;
	t_token *tmp_token;
	t_token *f_token;
	t_token *head;
	t_token *tokens;
	t_heredoc_kw *heredoc_head;
	t_heredoc_kw *heredoc;
	t_heredoc_str *heredoc_str_head;
	t_heredoc_str *heredoc_str;
	t_gc *gc_head;
	t_gc *gc_iterator;
	int heredoc_iterator;
	bool heredoc_active;
	int pipe_1;
	int pipe_0;
	char *heredoc_buff;
	int pipe_fd[2];
	int pipe_i;
	int pipe_o;
	int outfile_fd;
	int exit_status;
	int stdo;
	int stdi;
	int i;
	int j;
	char *line;
	char **paths;
	char *v_path;
	char **env;
	t_tools *p_tools;
	int rm;
	char *prompt;
	int quit_flag;
} g_vars;

typedef struct s_line
{
	char *cmd;
	char **params;
	char *line;
} t_line;

void ms_exec_rdr_child(bool has_pipe, int redirection, bool builtin, int sentence, int *pipe_fd);
int ms_exec_rdr_builtin(bool has_pipe, bool builtin, int sentence);
void ms_remove_redrets(int sentence);
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
void ms_copy_struct(t_env *s);
void ms_exec_builtin(char **sentence);
void ms_print_export(void);
t_env *ms_lstchr(char *s);
void ms_update_env_tail(void);
int ms_strncmp(char *a, char *b, char c);
void ms_run_unset(char *s);
void ms_toggle_signal(int get);
void ms_exit(char *msg, int stat);
void ms_add_env_list(char *s);
int ms_redirect_manage(int sentence);
int ms_check_executable(void);
int ms_redirect_parse(char **sentence);
void ms_prepare_tokens(void);
int ms_set_infile(char **pt, int index);
int ms_set_outfile(char **pt, int index, int mod);
int ms_set_heredoc(char **pt, int index);
void ms_signal_helper(int get);
void ms_put_status(t_token *token, int *i);
void ms_put_program_name(t_token *token, int *i);
void ms_delete_and_replace(int sentence, int start, int end);
int ms_is_redirect_index(int index);
t_heredoc_kw *ms_add_heredoc(void);
t_heredoc_str *ms_add_heredoc_str(void);
void ms_run_cd(char **sentence);
int ms_run_heredoc(void);
void ms_print_oldpwd(void);
void ms_run_pi(void);
void ms_run_echo(char **sentence);
void ms_run_pwd(void);
char *ms_get_env(char *s);
void add_gc_element(void *el);
t_gc *new_gc();
void ms_detective_leak(void);
void *ft_malloc(size_t num);
#endif
