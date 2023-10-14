/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_next_exec_builtin.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anargul <anargul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:54:06 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/10/14 10:49:37 by anargul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

void ms_run_pwd(void)
{
	char *s;

	s = ft_strdup(ms_getenv("PWD"));
	getcwd(s, ft_strlen(s));
	printf("%s\n", s);
	//free(s);
}

void ms_run_echo(char **sentence)
{
	bool n;
	int i;

	i = 1;
	n = false;
	while (sentence[i])
	{
		if (i == 1 && !ft_strncmp("-n", sentence[i], 2))
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
	char *pwd;
	char *opwd;
	int res;

	res = 0;
	pwd = ft_strdup(ms_get_env("PWD"));
	getcwd(pwd, ft_strlen(pwd));
	if (sentence[1] && !ft_strncmp(sentence[1], "-", 1))
	{
		res = chdir(ms_getenv("OLDPWD"));
		if (res == -1)
			return ((void)printf("[!] OLDPWD not set\n"));
		printf("%s\n", ms_getenv("OLDPWD"));
	}
	else if (sentence[1])
		res = chdir(sentence[1]);
	else if (!sentence[1])
		chdir(ms_getenv("HOME"));
	else
		return;
	if (res != -1)
	{
		opwd = ft_strjoin("OLDPWD=", pwd);
		if (!((ft_strlen(opwd) == ft_strlen(pwd)) && !ft_strncmp(opwd, pwd, ft_strlen(opwd))))
			ms_add_env_list(opwd);
		//free(pwd);
		pwd = ft_strdup(ms_get_env("PWD"));
		getcwd(pwd, ft_strlen(pwd));
		ms_add_env_list(ft_strjoin("PWD=", pwd));
	}
	else
		perror("minishell ");
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
				{
					//free(g_vars.env_list);
					g_vars.env_head = g_vars.env_head->next;
				}
				else if (g_vars.env_list == g_vars.env_tail)
				{
					prev->next = NULL;
					//free(g_vars.env_list);
				}
				else
				{
					prev->next = g_vars.env_list->next;
					//free(g_vars.env_list);
				}
				ms_update_env_tail();
				return;
			}
		}
		prev = g_vars.env_list;
		g_vars.env_list = g_vars.env_list->next;
	}
}
