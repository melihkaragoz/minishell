/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_redirect_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaragoz <mkaragoz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:39:35 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/10/12 13:41:10 by mkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"


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

int ms_redirect_parse(char **sentence)
{
	int i;
	int j;

	i = -1;
	while (g_vars.retred[++i])
	{
		if (!(sentence[g_vars.retred[i]->index + 1]))
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


