/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anargul <anargul@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:12:46 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/10/10 13:29:52 by anargul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"
void ms_run_herecoc(char **pt, char ***rt);
void ms_run_outfile(char **pt, int mod);
void ms_run_infile(char **pt);
void ms_run_redirect(void);

int main(void)
{
	ms_run_redirect();
	return (0);
}
void ms_run_redirect(void)
{
	int	stat;
	char ***rt;
	char *s = readline("minishell$ ");
	char **pt = ft_split(s, ' ');
	char *ex[3];

	ex[0] = ft_strdup(ft_strjoin("/bin/", pt[0]));
	ex[1] = 0;
	ex[2] = NULL;
	stat = 0;
	if (!(*pt))
		return;
	if ((pt[0] && pt[1]) && !ft_strncmp(pt[1], ">>", 2) && pt[2])
		ms_run_outfile(pt, 1);
	else if ((pt[0] && pt[1]) && !ft_strncmp(pt[1], ">", 1) && pt[2])
		ms_run_outfile(pt, 0);
	else if ((pt[0] && pt[1]) && !ft_strncmp(pt[1], "<<", 2))
		ms_run_herecoc(pt);
	else if ((pt[0] && pt[1]) && !ft_strncmp(pt[1], "<", 1))
		ms_run_infile(pt);
	int cp = fork();
	if (!cp)
		execve(ex[0], ex, 0);
	waitpid(cp, &stat, (int)NULL);
}

void ms_run_outfile(char **pt, int mod)
{
	int fd;

	if (!mod)
		fd = open(pt[2], O_RDWR | O_CREAT | O_TRUNC, 0777);
	else
		fd = open(pt[2], O_RDWR | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
		return ((void)printf("[!] dosya hatası.\n"));
	dup2(fd, 1);
	close(fd);
}

void ms_run_infile(char **pt)
{
	int	fd;
	fd = open(pt[2], O_RDONLY, 0777);
	if (fd == -1)
		return ((void)printf("[!] dosya hatası.\n"));
	dup2(fd, 0);
	close(fd);
}
