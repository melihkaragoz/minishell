/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_set_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anargul <anargul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:36:31 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/10/14 14:39:27 by anargul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

void ms_set_envlist(char **env)
{
	int i;

	i = -1;
	g_vars.env_list = ms_new_env();
	g_vars.env_head = g_vars.env_list;
	while (env[++i])
	{
		g_vars.env_list->content = env[i];
		g_vars.env_list->next = ms_new_env();
		g_vars.env_tail = g_vars.env_list;
		g_vars.env_list = g_vars.env_list->next;
	}
	g_vars.prompt = "\x1b[38;5;129mminishell$ \x1b[0m";
}
