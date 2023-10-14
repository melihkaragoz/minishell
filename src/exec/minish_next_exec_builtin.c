/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_next_exec_builtin.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anargul <anargul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:54:06 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/10/14 18:16:00 by anargul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

void ms_run_pwd(void)
{
	char *s;

	s = ft_strdup(ms_getenv("PWD"));
	getcwd(s, ft_strlen(s));
	printf("%s\n", s);
	// free(s);
}

int ms_check_echo_n(char *keyword)
{
	int i;

	i = 0;
	while (keyword[++i])
		if (keyword[i] != 'n')
			return (0);
	return (1);
}

void ms_run_echo(char **sentence)
{
	bool n;
	int i;

	i = 1;
	n = false;
	while (sentence[i])
	{
		if (i == 1 && !ft_strncmp("-n", sentence[i], 2) && ms_check_echo_n(sentence[i]))
		{
			n = true;
			i++;
			continue;
		}
		printf("%s", sentence[i]);
		if (sentence[i + 1])
			printf(" ");
		i++;
	}
	if (n == false)
		printf("\n");
}

void ms_run_cd(char **sentence)
{
	int res;
	char *oldpwd;
	char *curr_pwd;
	char *tmp;

	res = -1;
	oldpwd = ms_getenv("OLDPWD");
	curr_pwd = ft_malloc(ft_strlen(ms_getenv("PWD")) + 200);
	getcwd(curr_pwd, ft_strlen(ms_getenv("PWD")) + 200);
	add_gc_element(curr_pwd);
	if (sentence[1] && !ft_strncmp(sentence[1], "-", ft_strlen(sentence[1]) + 1))
	{
		if (oldpwd)
		{
			if (!(res = chdir(oldpwd))) // basarili
			{
				printf("%s\n", oldpwd);
				tmp = ft_strdup(curr_pwd);
				oldpwd = ft_strdup(tmp);
			}
		}
		else
			printf("minishell: OLDPWD not set");
	}
	else if (sentence[1])
	{
		if (!(res = chdir(sentence[1])))
			oldpwd = ft_strdup(curr_pwd);
		else
			perror("minishell : ");
	}
	else if (!sentence[1])
	{
		if (!(res = chdir(ms_getenv("HOME"))))
			oldpwd = ft_strdup(curr_pwd);
		else
			perror("minishell : ");
	}
	else
		perror("minishell : ");
	
	getcwd(curr_pwd, ft_strlen(ms_getenv("PWD")) + 200);
	add_gc_element(curr_pwd);
	ms_add_env_list(ft_strjoin("PWD=", curr_pwd));
	ms_add_env_list(ft_strjoin("OLDPWD=", oldpwd));
}

void ms_run_unset(char *s)
{
	t_env *prev;

	char *split;
	g_vars.env_list = g_vars.env_head;
	prev = g_vars.env_head;
	while (s && g_vars.env_list && g_vars.env_list->content)
	{
		split = ft_split(g_vars.env_list->content, '=')[0];
		if (ft_strlen(split) == ft_strlen(s))
		{
			if (!ft_strncmp(s, split, ft_strlen(split)))
			{
				if (g_vars.env_list == g_vars.env_head)
					g_vars.env_head = g_vars.env_head->next;
				else if (g_vars.env_list == g_vars.env_tail)
					prev->next = NULL;
				else
					prev->next = g_vars.env_list->next;
				ms_update_env_tail();
				return;
			}
		}
		prev = g_vars.env_list;
		g_vars.env_list = g_vars.env_list->next;
	}
}
