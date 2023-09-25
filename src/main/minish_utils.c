/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaragoz <mkaragoz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:10:46 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/09/26 02:33:57 by mkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_print_env(char **env)
{
	int	i;

	i = -1;
	if (!env)
		return (-1);
	while(env[++i])
		printf("%s\n",env[i]);
	return (0);
}

int	ms_set_path(char **env)
{
	int	i;

	i = -1;
	if (!env)
		return(-1);
	while (env[++i])
	{
		if(!(ft_strncmp(env[i], "PATH", 4)))
		{
			g_vars.paths = ft_split(env[i]+5, ':');
			break;
		}
	}
	return(0);
}

char	*ms_test_path(char *cmd)
{
	int		i;
	char	*new;
	char	*test_path;
	char	*path;
	char	**pt;

	i = -1;
	path = ms_getenv("PATH");
	if (!path)
		return (0);
	pt = ft_split(path, ':');
	if (!access(cmd, 0))
		return (cmd);
	while(pt[++i])
	{
		new = ft_strjoin(pt[i], "/");
		test_path = ft_strjoin(new, cmd);
		if(!access(test_path, 0) && ms_free_db_array(pt) && ms_free(new) && ms_free(path))
			return (test_path);
		ms_free(new);
		ms_free(test_path);
	}
	ms_free_db_array(pt);
	ms_free(path);
	return (NULL);
}

void	ms_free_tokens(void)
{
	free(g_vars.tokens);
	free(g_vars.f_token);
	free(g_vars.line);
	g_vars.i = 0;
	while (g_vars.paths[++(g_vars.i)])
		free(g_vars.paths[g_vars.i]);
}

int	ms_free_db_array(char **db)
{
	int	i;

	i = -1;
	while(db[++i])
		free(db[i]);
	return (1);
}

int	ms_free(char *s)
{
	free(s);
	return (1);
}
