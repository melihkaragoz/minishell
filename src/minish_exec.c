/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaragoz <mkaragoz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:54:08 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/07/08 01:36:31 by mkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_exec(void)
{
	int ev = -1;
	int	pid;
	char *prm[] = {"" ,NULL};

	pid = fork();
	if (pid == 0)
	{
		execve(g_vars.v_path, prm, g_vars.paths);
		exit(127);
	}
	waitpid(pid, NULL, 0);
	return (ev);
}


