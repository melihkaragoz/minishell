/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anargul <anargul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:43:10 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/10/14 16:44:10 by anargul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

int ms_strncmp(char *a, char *b, char c)
{
	return (ft_nstrchr(a, c) == ft_nstrchr(b, c) && !ft_strncmp(a, b, ft_nstrchr(a, c)));
}

void ms_update_env_tail(void)
{
	g_vars.env_tail = g_vars.env_head;
	while (g_vars.env_tail->next && g_vars.env_tail->next->content)
		g_vars.env_tail = g_vars.env_tail->next;
}

int ms_check_executable(void)
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
			return (0 && printf("minishell: syntax error near unexpected token `newline'\n"));
		else if (j == 0)
			return (0 && printf("minishell: syntax error near unexpected token `newline'\n"));
		i++;
	}
	return (1);
}

t_env *ms_lstchr(char *s)
{
	t_env *lst;

	lst = g_vars.env_head;
	add_gc_element(lst);
	while (lst && lst->content)
	{
		if (ms_strncmp(s, lst->content, '='))
			return (lst);
		lst = lst->next;
		add_gc_element(lst);
	}
	return (NULL);
}
