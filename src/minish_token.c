#include "minishell.h"

void ms_make_nodes(void)
{
	int f;
	char *new_content;

	g_vars.i = 0;
	while (g_vars.line && g_vars.line[g_vars.i])
	{
		while (g_vars.line[g_vars.i] && g_vars.line[g_vars.i] <= 32) // bosluklari gec
			(g_vars.i)++;
		f = g_vars.i;
		while (g_vars.line[g_vars.i] && (!ms_end_of_word() || g_vars.p_tools->arg_mode)) // ozel karakterleri gec
			(g_vars.i)++;
		new_content = ft_substr(g_vars.line, f, g_vars.i - f); // node'un oluştuğu bölüm
		g_vars.p_tools->arg_mode = true;
		if (*new_content)
		{
			g_vars.tokens->content = new_content;
			g_vars.tokens->next = ms_new_token();
			g_vars.tokens = g_vars.tokens->next;
		}
		else
			return ;
	}
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

void ms_set_tokens(void)
{
	ms_init_token();
	ms_init_tools();
	ms_make_nodes();
	ms_print_tokens();
	// free(g_vars.line);
}
