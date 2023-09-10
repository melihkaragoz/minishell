/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anargul <anargul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:04:24 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/09/10 10:17:28 by anargul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	ms_set_path(env);
	g_vars.env = env;
	while (42)
	{
		g_vars.line = readline("minishell$ "); // "ls -l | wc -l | touch";
		if (!g_vars.line && !(g_vars.line[0]))
			continue;
		add_history(g_vars.line);
		ms_set_tokens(); // parse part 1
		g_vars.tmp_token = g_vars.f_token;
		while (g_vars.f_token)
		{
			ms_check_env(g_vars.f_token);
			g_vars.f_token = g_vars.f_token->next;
		}
		ms_set_nodes();  // parse part 2
		ms_exec();
		
		int i = 0;
		int j;
		while (i < 3)
		{
			printf("%d\n", i);
			j = 0;
			while (g_vars.exec->av[i][j])
			{
				printf("%s \n", g_vars.exec->av[i][j]);
				j++;
			}
			printf("\n");
			i++;
		}
	}
	return (0);
}
