/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anargul <anargul@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:04:24 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/09/01 01:40:12 by anargul          ###   ########.fr       */
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
		g_vars.line = readline("minishell$ ");		// 	bu iki satırda g_vars.line'ın içine aynı şeyi atıyorsun. add_history 
		add_history(g_vars.line);					//yapıp parametre olarak vermek ile readline'ın dönüş değerine eşitlemek arasında ne fark var ?
		ms_set_tokens();
		// ms_print_tokens();
		// ms_exec();
		// printf("command not found: %s\n", g_vars.cmd);
	}

	return (0);
}
