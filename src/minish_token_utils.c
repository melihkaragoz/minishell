#include "minishell.h"

t_token *ms_new_token(void)
{
	t_token *n_token;

	n_token = malloc(sizeof(t_token));
	n_token->content = NULL;
	n_token->next = NULL;
	return (n_token);
}

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
	if (g_vars.line[g_vars.i + 1] == set)
	{
		g_vars.i++;
		g_vars.p_tools->quote_mode = 0;
	}	
}

void ms_init(void)
{
	g_vars.stdo = dup(1);
	g_vars.stdi = dup(0);;
	g_vars.exec = malloc(sizeof(t_exec));
	g_vars.exec->pipe_count = 0;
	g_vars.tokens = ms_new_token();
	g_vars.f_token = g_vars.tokens;
	g_vars.head = g_vars.tokens;
	g_vars.p_tools = malloc(sizeof(t_tools));
	g_vars.p_tools->quote_mode = 0;
	g_vars.p_tools->arg_mode = true;
}