/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_builtin_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaragoz <mkaragoz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:47:56 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/10/12 14:37:23 by mkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

char *ms_getenv(char *s) // bagli listeden cekiyor
{
	t_env *t;
	char **sp;
	char *val;
	int j;
	int k;

	t = g_vars.env_head;
	val = calloc(1, 1);
	while (t && t->content)
	{
		sp = ft_split(t->content, '=');
		if ((ft_strlen(sp[0]) == ft_strlen(s)) && !ft_strncmp(s, sp[0], ft_strlen(s)))
		{
			k = ft_strchr(t->content, '=') - t->content;
			val = malloc(sizeof(char) * ft_strlen(ft_strchr(t->content, '=')));
			j = -1;
			while (t->content[++k])
				val[++j] = t->content[k];
			val[++j] = 0;
			return (val);
		}
		t = t->next;
	}
	return (NULL);
}

char *ms_get_env(char *s) // bastaki env arrayinden cekiyor
{
	int i;
	char **tmp;
	i = -1;
	while (g_vars.env[++i])
	{
		tmp = ft_split(g_vars.env[i], '=');
		if (*tmp && !ft_strncmp(tmp[0], s, ft_strlen(s)))
			return (tmp[1]);
	}
	return (NULL);
}

void ms_print_export(void) // leak var
{
	t_env *t;
	char **s;
	int i;

	t = g_vars.env_head;
	while (t && t->content)
	{
		s = ft_split(t->content, '=');
		if (!s[1])
			s[1] = "";
		// printf("declare -x %s=\"%s\"\n", s[0], s[1]);
		printf("declare -x %s=\"", s[0]);
		i = 0;
		while (s[++i] && ft_strncmp(s[i], "", 1))
		{
			printf("%s", s[i]);
			if (s[i + 1] && ft_strncmp(s[i + 1], "", 1))
				printf("=\n");
		}
		printf("\"\n");
		t = t->next;
		// ms_free_db_array(s);
	}
}
