/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaragoz <mkaragoz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:23:29 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/09/05 22:22:54 by mkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ms_check_seperators(char *s)
{
	char seperators[4];
	int j;

	seperators[0] = '|';
	seperators[1] = '<';
	seperators[2] = '>';
	seperators[3] = 0;
	j = -1;
	while (seperators[++j])
		if (!ft_strncmp(s, &seperators[j], 1))
		{
			if (!ft_strncmp(s + 1, &seperators[j], 1))
				g_vars.p_tools->double_redirection = true;
			return (1);
		}
	return (0);
}

void	ms_set_quote_mode(int set)
{
	g_vars.p_tools->quote_mode = set;
	g_vars.p_tools->arg_mode = 1;
}

void	ms_set_arg_false(int i)
{
	if (i == 4 || i == 1 || i == 5 || i == 3)
		g_vars.i++;
	if (i == 4 || i == 1 || i == 5 || i == 0)
		g_vars.p_tools->arg_mode = false;
	if (i == 7 || i == 5)
		g_vars.p_tools->quote_mode = 0;
	if (i == 3)
		ms_set_quote_mode(g_vars.line[g_vars.i]);
	if (g_vars.p_tools->double_redirection == true && (i == 4))
	{
		g_vars.i++;
		g_vars.p_tools->double_redirection = false;
	}
}


int ms_check_schars(void)
{
	if (ms_check_seperators(&g_vars.line[g_vars.i]) && !g_vars.p_tools->quote_mode) // << >> || geldiyse burda geçiyor
		return (ms_set_arg_false(4), 1);
	while (g_vars.p_tools->quote_mode && g_vars.line[g_vars.i]) // tırnak açıldıysa
	{
		if (g_vars.line[g_vars.i] == g_vars.p_tools->quote_mode) // tırnak kapandıysa
		{
			if (g_vars.line[g_vars.i + 1] && (ms_check_seperators(&g_vars.line[g_vars.i + 1]) || g_vars.line[g_vars.i + 1] == ' ')) // tırnak kapandıysa --- bir sonraki karakter seperator ise
				return (ms_set_arg_false(5), 1);
			else if (g_vars.line[g_vars.i + 1] && (g_vars.line[g_vars.i + 1] == 39 || g_vars.line[g_vars.i + 1] == 34)) // tırnak kapandıysa --- bir sonraki karakter tırnaksa
				ms_set_arg_false(3);
			else
				return(ms_set_arg_false(7), 1); 		// tırnak kapandıysa --- bir sonraki karakter karakter ise
		}
		g_vars.i++;
	}
	if (g_vars.line[g_vars.i] && !g_vars.p_tools->quote_mode) // tırnak açık değilse
	{
		if (!ft_strncmp(&g_vars.line[g_vars.i], "'", 1) || !ft_strncmp(&g_vars.line[g_vars.i], "\"", 1)) // tırnak açık değilse --- tırnaksa
			ms_set_quote_mode(g_vars.line[g_vars.i]);
		else if (!ft_strncmp(&g_vars.line[g_vars.i], " ", 1)) // tırnak açık değilse --- boşluksa
			return (ms_set_arg_false(0),1);
		else if (g_vars.line[g_vars.i + 1] && ms_check_seperators(&g_vars.line[g_vars.i + 1])) // tırnak açık değilse --- bir sonraki karakter seperator ise
			return (ms_set_arg_false(1),1);
	}
	return (0);
}

void ms_init_token(void)
{
	// if (g_vars.tokens)
	// 	ms_free_tokens();
	g_vars.tokens = ms_new_token();
	g_vars.f_token = g_vars.tokens;
}

void ms_init_tools(void)
{
	g_vars.p_tools = malloc(sizeof(t_tools));
	g_vars.p_tools->quote_mode = 0;
	g_vars.p_tools->arg_mode = true;
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
	ms_init_tools();
	g_vars.i = 0;
	while (g_vars.line && g_vars.line[g_vars.i])
	{
		while (g_vars.line[g_vars.i] && g_vars.line[g_vars.i] <= 32) // bosluklari gec
			(g_vars.i)++;
		f = g_vars.i;
		while (g_vars.line[g_vars.i] && (!ms_check_schars() || g_vars.p_tools->arg_mode)) // ozel karakterleri gec
			(g_vars.i)++;
		new_content = ft_substr(g_vars.line, f, g_vars.i - f);
		printf("content: %s\n", new_content);
		g_vars.p_tools->arg_mode = true;
		if (*new_content)
		{
			g_vars.tokens->content = new_content;
			g_vars.tokens->next = ms_new_token();
			g_vars.tokens = g_vars.tokens->next;
		}
		else
			break;
	}
	ms_print_tokens();
	// free(g_vars.line);
}

void ms_print_tokens(void)
{
	t_token *t1;
	t1 = g_vars.f_token;
	while (t1)
	{
		printf("address:\t%p | content:\t%s.\t| next:\t%p\n", t1, t1->content, t1->next);
		t1 = t1->next;
	}
}
