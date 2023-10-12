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
	returnred = malloc(sizeof(t_return_red *) * (a + 1));
	for (int j = 0; j < a; j++) // for var
		returnred[j] = malloc(sizeof(t_return_red *));
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
	{
		dup2(g_vars.stdo, 1);
		return (printf("minishell: %s: No such file or directory\n", pt[index + 1]) && 1);
	}
	fd = open(pt[index + 1], O_RDONLY, 0777);
	if (fd == -1)
		return (printf("[!] dosya hatasi.\n") && 1);
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
	{
		return (printf("[!] dosya hatasi.\n") && 1);
	}
	dup2(fd, 1);
	close(fd);
	return (0);
}

int ms_set_heredoc(char **pt, int index)
{
	g_vars.heredoc->keyword = ft_strdup(pt[index + 1]);
	g_vars.heredoc->next = ms_add_heredoc();
	g_vars.heredoc = g_vars.heredoc->next;

	return (0);
}

int ms_run_heredoc(void)
{
	char *line;
	// int i;
	// int pipe_fd[2];

	// if (pipe(pipe_fd) == -1)
	// 	ft_putstr_fd("PIPE ERROR!\n", g_vars.stdo);
	// i = fork();
	// if (1)
	// {
	g_vars.heredoc = g_vars.heredoc_head;
	while (1)
	{
		line = readline("> ");
		if (g_vars.heredoc->next->keyword)
		{
			if (!ft_strncmp(line, g_vars.heredoc->keyword, ft_strlen(line) + 1))
				g_vars.heredoc = g_vars.heredoc->next;
			free(line);
			continue;
		}
		else if (!ft_strncmp(line, g_vars.heredoc->keyword, ft_strlen(line) + 1))
			return (0); // herecock bitti
		g_vars.heredoc_str->str = ft_strdup(line);
		g_vars.heredoc_str->next = ms_add_heredoc_str();
		g_vars.heredoc_str = g_vars.heredoc_str->next;
		free(line);
	}
	// exit(31);
	// }
	// waitpid(i, &g_vars.exit_status, 0);
	// i = -1;
	// while (g_vars.heredoc->str[++i])
	// 	ft_putstr_fd(g_vars.heredoc->str[i], pipe_fd[1]);		// pipe_fd
	// printf("%s\n", g_vars.heredoc->str[i]);
	// dup2(pipe_fd[0], 0);
	// close(pipe_fd[1]);
	// close(pipe_fd[0]);
	return (0);
}

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
		if (!ms_is_redirect_index(i)) // redirection DEĞİL ise                  < Makefile
		{
			if (detected_no_redirection == false) // ilk gelişi ise
			{
				detected_no_redirection = true;
				start = i; // başlangıcı belirle
				if (!g_vars.exec->av[sentence][i + 1])
				{
					ms_delete_and_replace(sentence, start, start + 1); // start'dan i'ye kadar olan bölümü tut gerisini sil
					return;
				}
			}
		}
		else // redirection ise
		{
			if (detected_no_redirection == true) // öncesinde redirection olmayan bir şey var ise
			{
				ms_delete_and_replace(sentence, start, i); // start'dan i'ye kadar olan bölümü tut gerisini sil
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
	bool hrdc;

	i = -1;
	hrdc = false;
	g_vars.heredoc_str = ms_add_heredoc_str();
	g_vars.heredoc_str_head = g_vars.heredoc_str;
	g_vars.heredoc_iterator = 0;
	g_vars.heredoc = ms_add_heredoc();
	;
	g_vars.heredoc_head = g_vars.heredoc;
	while (g_vars.retred[++i])
	{
		if (g_vars.retred[i]->type == 3) // <
		{
			if (ms_set_infile(g_vars.exec->av[sentence], g_vars.retred[i]->index))
				break; // return (1);
		}
		else if (g_vars.retred[i]->type == 4) // >
		{
			if (ms_set_outfile(g_vars.exec->av[sentence], g_vars.retred[i]->index, 0))
				break; // return (1);
		}
		else if (g_vars.retred[i]->type == 6) // >>
		{
			if (ms_set_outfile(g_vars.exec->av[sentence], g_vars.retred[i]->index, 1))
				break; // return (1);
		}
		else if (g_vars.retred[i]->type == 5)
		{
			hrdc = true;
			if (ms_set_heredoc(g_vars.exec->av[sentence], g_vars.retred[i]->index))
				break; // return (1);
		}
	}
	if (hrdc == true)
		ms_run_heredoc();

	g_vars.heredoc_str = g_vars.heredoc_str_head;
	// while (g_vars.heredoc_str->str)
	// {
	// 	printf("%s\n", g_vars.heredoc_str->str); // bunu pipe'a yaz sonra obur uctan okuyalim veya cat'e falan gonder
	// 	g_vars.heredoc_str = g_vars.heredoc_str->next;
	// }
	return (0);
}
