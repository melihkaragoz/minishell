/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anargul <anargul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:04:24 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/09/04 21:15:08 by anargul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	ms_set_path(env);
	g_vars.env = env;
	// char *str = malloc(sizeof(char) * 20);
	// str = "\"a\"\'a\'|";
	while (42)
	{
		g_vars.line = readline("minishell$ ");
		add_history(g_vars.line);
		ms_set_tokens();
	}
	return (0);
}

//   "a"'b'|
//   "a""b"|


