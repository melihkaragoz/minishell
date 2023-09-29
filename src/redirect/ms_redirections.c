#include "../main/minishell.h"

t_return_red *ms_isred_sentence(int sentence)
{
	int i;
	t_return_red *returnred;

	returnred = malloc(sizeof(t_return_red *));
	returnred->type = 0;
	i = -1;
	while (++i < g_vars.exec->arg_num)
	{
		// printf("%s, %d\n", g_vars.exec->av[sentence][i], g_vars.exec->av_token[sentence][i]);
		if (g_vars.exec->av_token[sentence][i] >= 3)
		{
			returnred->index = i;
			returnred->type = g_vars.exec->av_token[sentence][i];
			printf("rd: %s, rd type: %d\n", g_vars.exec->av[sentence][i], g_vars.exec->av_token[sentence][i]);
			return (returnred);
		}
		// return (g_vars.exec->av_token[sentence][i]);
	}
	return (0);
}

int ms_redirect_parse(char **sentence, int index)
{
	int i;

	if (!sentence[index + 1])
		return (printf("bash: syntax error near unexpected token `newline'\n") && 1);
	i = 0;
	while ((sentence[index + 1][i]))
	{
		if (!ft_isalnum(sentence[index + 1][i]))
			return (printf("bash: syntax error near unexpected token \'%c\'", sentence[index + 1][i]) && 1);
		i++;
	}
	return (0);
}

// void ms_set_infile()
// {
// }

void ms_set_outfile(char **pt, int index, int mod)
{
	int fd;

	printf("mod: %d\n", mod);
	if (!mod)
		fd = open(pt[index + 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	else
		fd = open(pt[index + 1], O_RDWR | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
		return ((void)printf("[!] dosya hatası.\n"));
	dup2(fd, 1);
	close(fd);
}

// void ms_set_heredoc() {}
void ms_remove_redrets(int sentence, int index)
{
	free(g_vars.exec->av[sentence][index]);
	free(g_vars.exec->av[sentence][index + 1]);
	g_vars.exec->av[sentence][index] = 0;
}

void ms_redirect_manage(int sentence, int type, int index)
{
	// if (type == 3) // <
	// 	ms_set_infile();
	if (type == 4) // >
		ms_set_outfile(g_vars.exec->av[sentence], index, 0);
	else if (type == 6) // >>
		ms_set_outfile(g_vars.exec->av[sentence], index, 1);
	// else if (type == 5) // <<
	// 	ms_set_heredoc();
}
