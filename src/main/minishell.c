/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaragoz <mkaragoz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:04:24 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/09/26 14:01:18 by mkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_check_executable(void)
{
	int i;
	int j;

	i = 0;
	while (i <= g_vars.exec->pipe_count)
	{
		j = 0;
		while (g_vars.exec->av[i][j])
			j++;
		if (j == 1 && g_vars.exec->av_token[i][j - 1] == 5)
		{
			printf("bash: syntax error near unexpected token \'||\'\n");
			return (0);
		}
		else if (j == 0)
		{
			printf("bash: syntax error near unexpected token \'|\'\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	ms_set_path(env);
	int sentence_it;
	g_vars.env = env;
	ms_set_envlist(env);
	signal(SIGQUIT, ms_toggle_signal);
	signal(SIGINT, ms_toggle_signal);
	while (42)
	{
		g_vars.rm = 0;
		g_vars.line = readline(g_vars.prompt);
		if (!(g_vars.line) && printf("\a"))
			ms_exit("", 1);
		if (!(*(g_vars.line)) || g_vars.rm)
			continue;
		add_history(g_vars.line);
		ms_set_tokens(); // parse part 1
		g_vars.tmp_token = g_vars.f_token;
		while (g_vars.f_token->content)
		{
			ms_check_env(g_vars.f_token);
			g_vars.f_token = g_vars.f_token->next;
		}
		ms_set_nodes();		 // parse part 2
		ms_set_execve_arg(); // g_vars.exec->av oluşturulur.
		if (!ms_check_executable())
			continue ;
		g_vars.i = -1;
		sentence_it = g_vars.exec->pipe_count + 1;
		while (++g_vars.i < sentence_it)
			ms_exec(g_vars.i);
		dup2(g_vars.stdo, 1);
		dup2(g_vars.stdi, 0);
	}
	return (0);
}
