/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anargul <anargul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:04:24 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/09/09 13:00:20 by anargul          ###   ########.fr       */
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
		// "echo \"deneme $PWD\"";
		g_vars.line = readline("minishell$ ");
		if (!g_vars.line && !(g_vars.line[0]))
			continue;
		add_history(g_vars.line);
		ms_set_tokens(); // parse part 1
		g_vars.tmp_token = g_vars.f_token;
		while (g_vars.f_token)
		{
			ms_check_env(g_vars.f_token);
			printf("new: %s\n", g_vars.f_token->content);
			g_vars.f_token = g_vars.f_token->next;
		}
		ms_set_nodes();  // parse part 2
		ms_exec();
		printf("\n\nASD\n\n");
		getchar();
	}
	return (0);
}
