#include "minishell.h"

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

void	ms_add_quotes_to_last(void)
{
	char *tmp;

	tmp = g_vars.line;
	free(g_vars.line);
	g_vars.line = ft_strjoin(tmp, "\"");
}

int ms_end_of_word(void)
{
	if (ms_check_seperators(&g_vars.line[g_vars.i]) && !g_vars.p_tools->quote_mode) // << >> || geldiyse burda geçiyor
		return (ms_set_arg_false(4), 1);
	while (g_vars.p_tools->quote_mode && g_vars.line[g_vars.i] && g_vars.i++) // tırnak açıldıysa
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
		else if (g_vars.line[g_vars.i + 1] == '\0')
			ms_add_quotes_to_last();
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

