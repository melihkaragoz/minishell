/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anargul <anargul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:04:24 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/09/10 15:54:19 by anargul          ###   ########.fr       */
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
		g_vars.line =  readline("\x1b[38;5;129mminishell$ \x1b[0m");//"ls -l | grep \"py\""; //
		if ((!(g_vars.line) || !(*(g_vars.line))) && printf("\a"))
			continue ;
		add_history(g_vars.line);
		ms_set_tokens(); // parse part 1
		g_vars.tmp_token = g_vars.f_token;
		while (g_vars.f_token)
		{
			ms_check_env(g_vars.f_token);
			g_vars.f_token = g_vars.f_token->next;
		}
		ms_set_nodes();  // parse part 2
    	ms_set_execve_av2(); // g_vars.exec->av oluşturulur.
		g_vars.i = -1;
		int zort = g_vars.exec->pipe_count + 1;
		while (++g_vars.i < zort)
			ms_exec(g_vars.i);
		dup2(g_vars.stdo, 1);
		dup2(g_vars.stdi, 0);
		// int i = 0;
		// int j;
		// while (i < 3)
		// {
		// 	printf("%d\n", i);
		// 	j = 0;
		// 	while (g_vars.exec->av[i][j])
		// 	{
		// 		printf("%s \n", g_vars.exec->av[i][j]);
		// 		j++;
		// 	}
		// 	printf("\n");
		// 	i++;
		// }
		// exit(31);
	}
	return (0);
}
