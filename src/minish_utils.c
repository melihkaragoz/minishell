/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaragoz <mkaragoz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:10:46 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/07/07 23:46:29 by mkaragoz         ###   ########.fr       */
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

	i = -1;
	while(g_vars.paths[++i])
	{
		new = ft_strjoin(g_vars.paths[i], "/");
		test_path = ft_strjoin(new, cmd);
		if(!access(test_path, 0))
			return (test_path);
	}
	return (NULL);
}
