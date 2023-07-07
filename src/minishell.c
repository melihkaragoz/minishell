/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaragoz <mkaragoz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:04:24 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/07/08 01:45:36 by mkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	ms_set_path(env);
	while (42)
	{
		g_vars.line = readline("minishell$ ");
		g_vars.cmd = ms_get_cmd();
		g_vars.v_path = ms_test_path(g_vars.cmd);
		if (g_vars.v_path)
		{
			ms_exec();
			// ms_free_struct();
		}
		else
			printf("command not found: %s\n", g_vars.cmd);
	}

	return (0);
}
