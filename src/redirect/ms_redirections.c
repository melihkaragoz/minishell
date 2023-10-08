#include "../main/minishell.h"

t_return_red **ms_isred_sentence(int sentence)
{
	int i;
	int j;
	int a;
	t_return_red **returnred;

	i = -1;
	a = 0;
	while (g_vars.exec->av[sentence][++i])
		if (g_vars.exec->av[sentence][i] && (g_vars.exec->av_token[sentence][i] >= 3 || g_vars.exec->av_token[sentence][i] <= 8))
			a++;
	if (a == 0)
		return (0);
	else
	{
		returnred = malloc(sizeof(t_return_red *) * (a + 1));
		returnned[a] = NULL;
		i = -1;
		j = 0;
		while (g_vars.exec->av[sentence][++i])
		{
			if (a == 0)
				return (returnred);
			if (g_vars.exec->av_token[sentence][i] >= 3)
			{
				returnred[j]->index = i;
				returnred[j]->type = g_vars.exec->av_token[sentence][i];
				a--;
				j++;
			}
		}
		return (returnred);
	}
}

int ms_redirect_parse(char **sentence, int index)
{
	int i;

	if (!sentence[index + 1])
		return (printf("minishell: syntax error near unexpected token `newline'\n") && 1);
	i = 0;
	while ((sentence[index + 1][i]))
	{
		if (!ft_isalnum(sentence[index + 1][i]))
			return (printf("minishell: syntax error near unexpected token \'%c\'\n", sentence[index + 1][i]) && 1);
		i++;
	}
	return (0);
}

int ms_set_infile(char **pt, int index)
{
	int fd;
	if (access(pt[index + 1], 0))
		return (printf("minishell: %s: No such file or directory\n", pt[index + 1]) && 1);
	fd = open(pt[index + 1], O_RDONLY, 0777);
	if (fd == -1)
		return (printf("[!] dosya hatası.\n") && 1);
	dup2(fd, 0);
	close(fd);
	return (0);
}

int ms_set_outfile(char **pt, int index, int mod)
{
	int fd;

	if (!mod)
		fd = open(pt[index + 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	else
		fd = open(pt[index + 1], O_RDWR | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
		return (printf("[!] dosya hatası.\n") && 1);
	dup2(fd, 1);
	close(fd);
	return (0);
}

// void ms_set_heredoc(char **pt, int index)
// {
// 	// t_heredoc	*hd_start;
// 	// char	*line;
// 	// int	fd;

// 	// // do syntax check
// 	// fd = open(pt[index + 1], O_RDWR | O_CREAT, 0777);
// 	// line = readline(">> ");
// 	// while()
// 	exit(30);
// }
void ms_remove_redrets(int sentence, int index)
{
	free(g_vars.exec->av[sentence][index]);
	free(g_vars.exec->av[sentence][index + 1]);
	g_vars.exec->av[sentence][index] = 0;
}

int ms_redirect_manage(int sentence, int type, int index)
{
	if (type == 3) // <
	{
		if (ms_set_infile(g_vars.exec->av[sentence], index))
			return (1);
	}
	if (type == 4) // >
	{
		if (ms_set_outfile(g_vars.exec->av[sentence], index, 0))
			return (1);
	}
	else if (type == 6) // >>
	{
		if (ms_set_outfile(g_vars.exec->av[sentence], index, 1))
			return (1);
	}
	// else if (type == 5) // <<
	// ms_set_heredoc(g_vars.exec->av[sentence], index);
	return (0);
}
