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
		if (g_vars.exec->av[sentence][i] && (g_vars.exec->av_token[sentence][i] >= 3 && g_vars.exec->av_token[sentence][i] <= 8))
			a++;
	g_vars.exec->red_count = a;
	if (a == 0)
		return (0);
	else
	{
		returnred = malloc(sizeof(t_return_red *) * (a + 1));
		for (int j = 0; j < a; j++)
		{
			printf("+");
			returnred[j] = malloc(sizeof(t_return_red *));
		}
		printf("a: %d\n", a);
		i = -1;
		j = 0;
		while (g_vars.exec->av[sentence][++i])
		{
			if (!a)
				return (returnred);
			if (g_vars.exec->av_token[sentence][i] >= 3 && g_vars.exec->av_token[sentence][i] <= 8)
			{
				returnred[j]->index = i;
				returnred[j]->type = g_vars.exec->av_token[sentence][i];
				a--;
				j++;
			}
		}
		returnred[g_vars.exec->red_count] = 0;
		return (returnred);
	}
}

int ms_redirect_parse(char **sentence)
{
	int i;
	int j;

	i = -1;
	while (g_vars.retred[++i])
	{
		if (!sentence[g_vars.retred[i]->index + 1])
			return (printf("minishell: syntax error near unexpected token `newline'\n") && 1);
		j = -1;
		while ((sentence[g_vars.retred[i]->index + 1][++j]))
			if (!ft_isalnum(sentence[g_vars.retred[i]->index + 1][j]))
				return (printf("minishell: syntax error near unexpected token \'%c\'\n", sentence[g_vars.retred[i]->index + 1][j]) && 1);
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

int ms_is_redirect_index(int index)
{
	int i;

	i = 0;
	while (g_vars.retred[i])
	{
		if (g_vars.retred[i]->index == index)
			return (1);
		i++;
	}
	return (0);
}

void ms_delete_and_replace(int sentence, int start, int end)
{
	char **str;
	int i;

	str = malloc(sizeof(char *) * (end - start + 2));
	str[end - start + 1] = NULL;
	i = 0;
	while (start < end)
	{
		str[i] = ft_strdup(g_vars.exec->av[sentence][start]);
		i++;
		start++;
	}
	i = 0;
	while (g_vars.exec->av[sentence][i])
	{
		free(g_vars.exec->av[sentence][i]);
		i++;
	}
	g_vars.exec->av[sentence] = str;
}

void ms_remove_redrets(int sentence)
{
	int i;
	int start;
	bool detected_no_redirection;

	detected_no_redirection = false;
	i = 0;
	while (g_vars.exec->av[sentence][i]) // kelimelerin döngüsü
	{
		printf("[145]: %s\n", g_vars.exec->av[sentence][i]);
		if (!ms_is_redirect_index(i)) // redirection DEĞİL ise
		{
			printf("no redirection in: %d\n", i);
			if (detected_no_redirection == false) // ilk gelişi ise
			{
				printf("ilk gelisi\n");
				detected_no_redirection = true;
				start = i; // başlangıcı belirle
			}
		}
		else // redirection ise
		{
			if (detected_no_redirection == true) // öncesinde redirection olmayan bir şey var ise
			{
				printf("redirect bitti in%d\n", i);
				ms_delete_and_replace(sentence, start, i); // start'dan i'ye kadar olan bölümü tut gerisini sil
				ft_putstr_fd("SENTENCE KELİME AREA\n", g_vars.stdo);
				for (int a = 0; g_vars.exec->av[sentence][a]; a++)
				{
					ft_putstr_fd(g_vars.exec->av[sentence][a], g_vars.stdo);
				}
				ft_putstr_fd("\nSENTENCE KELİME AREA FINISH ---------------\n", g_vars.stdo);
				return;
			}
			i++; // redirection yanında bir kelime daha almak zorunda olduğu için onu atlıyoruz
		}
		i++;
	}
}

int ms_redirect_manage(int sentence)
{
	int i;

	i = -1;
	while (g_vars.retred[++i])
	{
		if (g_vars.retred[i]->type == 3) // <
		{
			if (ms_set_infile(g_vars.exec->av[sentence], g_vars.retred[i]->index))
				return (1);
		}
		if (g_vars.retred[i]->type == 4) // >
		{
			if (ms_set_outfile(g_vars.exec->av[sentence], g_vars.retred[i]->index, 0))
				return (1);
		}
		else if (g_vars.retred[i]->type == 6) // >>
		{
			if (ms_set_outfile(g_vars.exec->av[sentence], g_vars.retred[i]->index, 1))
				return (1);
		}
	}

	// else if (type == 5) // <<
	// ms_set_heredoc(g_vars.exec->av[sentence], index);
	return (0);
}
