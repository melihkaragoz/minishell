/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_run_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anargul <anargul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:44:43 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/10/14 10:50:57 by anargul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"


void ms_copy_struct(t_env *src)
{
	t_env *s;
	t_env *d;

	d = ms_new_env();
	s = src;
	g_vars.export_list = d;
	g_vars.export_head = d;
	while (s->content)
	{
		d->content = ft_strdup(s->content);
		d->next = ms_new_env();
		d = d->next;
		s = s->next;
	}
}

void ms_add_env_list(char *s)
{
	t_env *te;

	te = ms_lstchr(s);
	if (te && te->content)
	{
		te->content = s;
		return;
	}
	g_vars.env_tail->next = ms_new_env();
	g_vars.env_tail->next->content = ft_strdup(s);
	g_vars.env_tail = g_vars.env_tail->next;
	g_vars.env_tail->next = NULL;
}

t_heredoc_kw *ms_add_heredoc(void)
{
	t_heredoc_kw *hd;

	hd =ft_malloc(sizeof(t_heredoc_kw));
	hd->keyword = NULL;
	hd->next = NULL;
	return (hd);
}

t_heredoc_str *ms_add_heredoc_str(void)
{
	t_heredoc_str *hd;

	hd =ft_malloc(sizeof(t_heredoc_str));
	hd->str = NULL;
	hd->next = NULL;
	return (hd);
}
