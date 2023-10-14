/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_exec_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anargul <anargul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:50:45 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/10/14 10:53:04 by anargul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

void ms_exec_builtin(char **sentence)
{
	if (!ft_strncmp(sentence[0], "echo", 5))
		ms_run_echo(sentence);
	else if (!ft_strncmp(sentence[0], "pwd", 4))
		ms_run_pwd();
	else if (!ft_strncmp(sentence[0], "env", 4))
		ms_run_env();
	else if (!ft_strncmp(sentence[0], "export", 7) && !sentence[1])
		ms_print_export();
	else if (!ft_strncmp(sentence[0], "export", 7))
		return;
	else if (!ft_strncmp(sentence[0], "cd", 3) && (sentence[1] && !ft_strncmp(sentence[1], "-", 2)))
		ms_print_oldpwd();
	else if (!ft_strncmp(sentence[0], "cd", 3))
		return;
	else if (!ft_strncmp(sentence[0], "π", 3))
		ms_run_pi();
	else
	{
		const char *errmsg = ft_strjoin("bash: ", sentence[0]);
		errmsg = ft_strjoin(errmsg, " command not found");
		printf("%s\n", errmsg);
	}
}

void ms_run_env(void)
{
	t_env *lst;

	lst = g_vars.env_head;
	while (lst && lst->content)
	{
		printf("%s\n", lst->content);
		lst = lst->next;
	}
}

void ms_run_export(char *s)
{
	char **sp;

	if (g_vars.export_list && !g_vars.export_list->next)
	{
		g_vars.export_tail = g_vars.env_tail;
		ms_copy_struct(g_vars.env_head);
	}
	if (!s)
		ms_print_export();
	else
	{
		sp = ft_split(s, '=');
		if (sp[1])
			ms_add_env_list(s);
	}
}

void ms_print_oldpwd(void)
{
	if (ms_getenv("OLDPWD") == NULL)
		printf("bash: cd: OLDPWD not set\n");
	else
		printf("%s\n", ms_getenv("OLDPWD"));
}

void ms_run_pi(void)
{
	int fd;
	char *str;

	fd = open("../π.txt", O_RDONLY);
	if (fd < 1)
		return;
	str = get_next_line(fd);
	while (str)
	{
		printf("%s\n", str);
		free(str);
		str = get_next_line(fd);
	}
}
