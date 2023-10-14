/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anargul <anargul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:10:46 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/10/14 14:38:22 by anargul          ###   ########.fr       */
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
		if (!access(test_path, 0)){
			return (test_path);
		}
	}
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
	ms_set_nodes();
	ms_set_execve_arg();
}