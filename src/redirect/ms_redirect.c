/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaragoz <mkaragoz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:12:46 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/09/26 14:52:20 by mkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"
void ms_run_outfile(char **pt, int mod);
void ms_run_infile(char **pt, int mod);
void ms_run_redirect(void);

int main(void)
{
	ms_run_redirect();
	return(0);
}
void ms_run_redirect(void)
{
	char *s = readline("minishell$ ");
	char **pt = ft_split(s, ' ');
	char *ex[3];

	ex[0] = ft_strdup(ft_strjoin("/bin/", pt[0]));
	ex[1] = ft_strdup(pt[1]);
	ex[2] = NULL;
	if (!(*pt))
		return;
	if ((pt[1] && pt[2]) && !ft_strncmp(pt[2], ">>", 2) && pt[3])
		ms_run_outfile(pt, 1);
	else if ((pt[1] && pt[2]) && !ft_strncmp(pt[2], ">", 1) && pt[3])
		ms_run_outfile(pt, 0);
	else if ((pt[1] && pt[2]) && !ft_strncmp(pt[2], "<<", 2))
		ms_run_infile(pt, 1);
	else if ((pt[1] && pt[2]) && !ft_strncmp(pt[2], "<", 1))
		ms_run_infile(pt, 0);
	int cp = fork();
	if (!cp)
	{
		execve(ex[0], ex, NULL);
	}
}

void ms_run_outfile(char **pt, int mod)
{
	int fd;

	if (!mod)
		fd = open(pt[3], O_RDWR | O_CREAT | O_TRUNC, 0777);
	else
		fd = open(pt[3], O_RDWR | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
		return ((void)printf("[!] dosya hatası.\n"));
	printf("fd: %d\n", fd);
	dup2(fd, 1);
	close(fd);
}

void ms_run_infile(char **pt, int mod) {}
