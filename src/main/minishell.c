/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anargul <anargul@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:04:24 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/10/12 20:21:11 by anargul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	int sentence_it;
	ms_set_path(env);
	g_vars.env = env;
	g_vars.exit_status = 0;
	g_vars.ff = 0;
	ms_set_envlist(env);
	signal(SIGQUIT, ms_signal_helper);
	signal(SIGINT, ms_toggle_signal);
	while (42)
	{
		g_vars.heredoc_active = false; // jskdjaskldjaklsfklasfasf
		g_vars.rm = 0;
		g_vars.line = readline(g_vars.prompt);
		if (!(g_vars.line) && printf("\a"))
			ms_exit("", 1);
		if (!(*(g_vars.line)) || g_vars.rm)
			continue;
		ms_prepare_tokens();
		if (!ms_check_executable())
			continue;
		g_vars.i = -1;
		sentence_it = g_vars.exec->pipe_count + 1;
		while (++g_vars.i < sentence_it)
			ms_exec(g_vars.i);
		dup2(g_vars.stdo, 1);
		dup2(g_vars.stdi, 0);
	}
	return (0);
}
