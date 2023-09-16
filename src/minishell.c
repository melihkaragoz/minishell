/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaragoz <mkaragoz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:04:24 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/09/16 16:14:52 by mkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	ms_set_path(env);
	int sentence_it;
	g_vars.env = env;
	ms_set_envlist(env);
	while (42)
	{
		g_vars.line = readline("\x1b[38;5;129mminishell$ \x1b[0m"); //"ls -l | grep \"py\""; //
		if ((!(g_vars.line) || !(*(g_vars.line))) && printf("\a"))
			continue;
		add_history(g_vars.line);
		ms_set_tokens(); // parse part 1
		g_vars.tmp_token = g_vars.f_token;
		while (g_vars.f_token)
		{
			ms_check_env(g_vars.f_token);
			g_vars.f_token = g_vars.f_token->next;
		}
		ms_set_nodes();		 // parse part 2
		ms_set_execve_arg(); // g_vars.exec->av oluşturulur.
		//ms_print_tokens();
		g_vars.i = -1;
		sentence_it = g_vars.exec->pipe_count + 1;
		while (++g_vars.i < sentence_it)
			ms_exec(g_vars.i);
		// ms_run_env();
		dup2(g_vars.stdo, 1);
		dup2(g_vars.stdi, 0);
	}
	return (0);
}
