/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaragoz <mkaragoz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:10:46 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/10/12 13:38:44 by mkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

int ms_print_env(char **env)
{
	int i;

	i = -1;
	if (!env)
		return (-1);
	while (env[++i])
		printf("%s\n", env[i]);
	return (0);
}

int ms_set_path(char **env)
{
	int i;

	i = -1;
	if (!env)
		return (-1);
	while (env[++i])
	{
		if (!(ft_strncmp(env[i], "PATH", 4)))
		{
			g_vars.paths = ft_split(env[i] + 5, ':');
			break;
		}
	}
	return (0);
}

char *ms_test_path(char *cmd)
{
	int i;
	char *new;
	char *test_path;
	char *path;
	char **pt;

	i = -1;
	path = ms_getenv("PATH");
	if (!path || !(*cmd))
		return (0);
	pt = ft_split(path, ':');
	if (!access(cmd, X_OK))
		return (cmd);
	while (pt[++i])
	{
		new = ft_strjoin(pt[i], "/");
		test_path = ft_strjoin(new, cmd);
		if (!access(test_path, 0) && ms_free_db_array(pt) && ms_free(new) && ms_free(path))
			return (test_path);
		ms_free(new);
		ms_free(test_path);
	}
	ms_free_db_array(pt);
	ms_free(path);
	return (NULL);
}

void ms_prepare_tokens(void)
{
	add_history(g_vars.line);
	ms_set_tokens(); // parse part 1
	g_vars.tmp_token = g_vars.f_token;
	while (g_vars.f_token->content)
	{
		ms_check_env(g_vars.f_token);
		g_vars.f_token = g_vars.f_token->next;
	}
	ms_set_nodes();		 // parse part 2
	ms_set_execve_arg(); // g_vars.exec->av oluşturulur.
}

void ms_free_tokens(void)
{
	free(g_vars.tokens);
	free(g_vars.f_token);
	free(g_vars.line);
	g_vars.i = 0;
	while (g_vars.paths[++(g_vars.i)])
		free(g_vars.paths[g_vars.i]);
}

// void	ms_free_heredoc(t_heredoc *hd)
// {
// 	t_heredoc	*start;

// 	start = hd;
// 	while (start)
// 	{
// 		free(start->content);
// 		start = start->next;
// 		start ->=
// 	}
// }
