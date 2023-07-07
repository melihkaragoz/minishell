/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaragoz <mkaragoz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:10:46 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/07/07 22:42:23 by mkaragoz         ###   ########.fr       */
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

int	ms_test_path()
