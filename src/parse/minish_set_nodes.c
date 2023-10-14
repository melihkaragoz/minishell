/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_set_nodes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anargul <anargul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:41:24 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/10/14 10:49:37 by anargul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

void ms_node_remove_char(t_token *tmp, int i) // birinci parametre olarak verilen stringden ikinci parametre indexindeki karakteri siler.
{
	char *tmp_str;
	char *tmp_str_extra;
	int len;

	if (tmp->content && *tmp->content)
	{
		len = ft_strlen(tmp->content);
		tmp_str = ft_substr(tmp->content, 0, i);
		tmp_str_extra = ft_substr(tmp->content, i + 1, len - i);
		//free(tmp->content);
		tmp->content = ft_strjoin(tmp_str, tmp_str_extra);
		//free(tmp_str);
		//free(tmp_str_extra);
	}
}

void ms_remove_quotes(t_token *tmp)
{
	int quo;
	int start_pos_quo;

	g_vars.i = 0;
	quo = 0;
	while (tmp->content[g_vars.i])
	{
		if (quo && tmp->content[g_vars.i] == quo)
		{
			quo = 0;
			ms_node_remove_char(tmp, start_pos_quo);
			ms_node_remove_char(tmp, g_vars.i - 1);
			g_vars.i -= 2;
		}
		else if (!quo && (tmp->content[g_vars.i] == '\'' || tmp->content[g_vars.i] == '\"'))
		{
			quo = tmp->content[g_vars.i];
			start_pos_quo = g_vars.i;
		}
		g_vars.i++;
	}
}

int ms_node_check_builtin(char *content)
{
	if (!content)
		return (0);
	if (!ft_strncmp("echo", content, 5))
		return (1);
	else if (!ft_strncmp("pwd", content, 4))
		return (1);
	else if (!ft_strncmp("export", content, 7))
		return (1);
	else if (!ft_strncmp("unset", content, 6))
		return (1);
	else if (!ft_strncmp("env", content, 4))
		return (1);
	else if (!ft_strncmp("exit", content, 5))
		ms_exit ("exit",0);
	else if (!ft_strncmp("cd", content, 3))
		return (1);
	else if (!ft_strncmp("π", content, 3))
		return (1);
	return (0);
}

int ms_node_check_redirection(char *content)
{
	if (!ft_strncmp("<<", content, 2))
		return (5);
	else if (!ft_strncmp("<", content, 1))
		return (3);
	else if (!ft_strncmp(">>", content, 2))
		return (6);
	else if (!ft_strncmp(">", content, 1))
		return (4);
	else if (!ft_strncmp("||", content, 2))
		return (7);
	else if (!ft_strncmp("&&", content, 2))
		return (8);
	return (0);
}

void ms_set_nodes(void)
{
	while (g_vars.tmp_token->content) // node'ları tek tek gezen döngü
	{
		g_vars.tmp_token->type = 0;								  // undefined
		if (ms_node_check_redirection(g_vars.tmp_token->content)) // redirection
			g_vars.tmp_token->type = ms_node_check_redirection(g_vars.tmp_token->content);
		else if (!ft_strncmp("|", g_vars.tmp_token->content, 1)) // pipe
		{
			g_vars.tmp_token->type = 2;
			g_vars.exec->pipe_count++; // pipe sayısı
		}
		ms_remove_quotes(g_vars.tmp_token);
		if (ms_node_check_builtin(g_vars.tmp_token->content)) // built-in
			g_vars.tmp_token->type = 1;
		// printf("content: .%s. - type: %d\n", g_vars.tmp_token->content, g_vars.tmp_token->type);
		g_vars.tmp_token = g_vars.tmp_token->next;
	}
}
