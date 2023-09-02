/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaragoz <mkaragoz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:23:29 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/09/03 02:20:21 by mkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ms_cmp(int i, char c)
{
	return (g_vars.line[i] == c);
}

int ms_check_schars(int j)
{
	if (g_vars.line[j])
		if (ms_cmp(j, ' ')) // || ms_cmp(j, '<<') || ms_cmp(j, '>>') || ms_cmp(j, '|') || ms_cmp(j, '<') || ms_cmp(j, '>') || ms_cmp(j, '\'') || ms_cmp(j, '\"') eklenecek.
			return (1);
	return (0);
}

void ms_init_token(void)
{
	// if (g_vars.tokens)
	// 	ms_free_tokens();
	g_vars.tokens = ms_new_token();
	g_vars.f_token = g_vars.tokens;
}

t_token *ms_new_token(void)
{
	t_token *n_token;

	n_token = malloc(sizeof(t_token));
	n_token->content = NULL;
	n_token->next = NULL;
	return (n_token);
}

void ms_set_tokens(void)
{
	int f;
	char *new_content;

	ms_init_token();
	g_vars.i = 0;
	while (g_vars.line && g_vars.line[g_vars.i])
	{
		while (g_vars.line[g_vars.i] && g_vars.line[g_vars.i] <= 32) // bosluklari gec
			(g_vars.i)++;
		f = g_vars.i;					   // bosluk olmayan ilk karakterin indexi
		while (!ms_check_schars(g_vars.i)) // ozel karakter kontrolu yap
			(g_vars.i)++;
		new_content = ft_substr(g_vars.line, f, g_vars.i - f); // keywordu token olarak al
		if (*new_content)
		{
			// int k = 0;
			// while(new_content[k])
			// 	printf("-%i",new_content[k++]);
			g_vars.tokens->content = new_content;
			g_vars.tokens->next = ms_new_token();
			g_vars.tokens = g_vars.tokens->next;
			// printf("\nimlec: %i-[%c]\n",g_vars.line[g_vars.i],g_vars.line[g_vars.i]);
		}
		else
			break;
		if (g_vars.line[g_vars.i])
			g_vars.i++;
	}
	ms_print_tokens();
	free(g_vars.line);
}

void ms_print_tokens(void)
{
	int i;

	i = 0;
	t_token *t1;
	t1 = g_vars.f_token;
	while (t1)
	{
		printf("address:\t%p | content:\t%s\t| next:\t%p\n", t1, t1->content, t1->next);
		t1 = t1->next;
	}
}
