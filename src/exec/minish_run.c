/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_run.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anargul <anargul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:44:58 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/10/14 11:32:33 by anargul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

void ms_set_execve_arg(void)
{
	t_token *tmp;
	t_token *tmp2;
	int sentence;
	int i;

	i = 0;
	sentence = -1;
	tmp = g_vars.head;
	tmp2 = g_vars.head;
	g_vars.exec->av_token = ft_malloc(sizeof(int *) * (g_vars.exec->pipe_count + 1));
	g_vars.exec->av_token[g_vars.exec->pipe_count] = NULL;
	g_vars.exec->av = ft_malloc(sizeof(char **) * (g_vars.exec->pipe_count + 1));
	g_vars.exec->av[g_vars.exec->pipe_count] = NULL;
	g_vars.i = 0;
	g_vars.exec->arg_num = 0;
	while (tmp)
	{
		if (tmp->type == 2 || !(tmp->content)) // herhangi bir biten cümle'yi farket
		{
			g_vars.exec->set_path = 0;
			sentence++;
			g_vars.exec->av_token[sentence] = ft_malloc(sizeof(int) * (g_vars.i + 1));
			g_vars.exec->av_token[sentence][g_vars.i] = 0;
			g_vars.exec->av[sentence] = ft_malloc(sizeof(char *) * (g_vars.i + 1));
			g_vars.exec->av[sentence][g_vars.i] = NULL;
			i = -1;
			while (++i < g_vars.i)
			{
				g_vars.exec->arg_num++;
				g_vars.exec->av[sentence][i] = ft_strdup(tmp2->content);
				g_vars.exec->av_token[sentence][i] = tmp2->type;
				if (!(tmp2->type) && !(g_vars.exec->set_path) && i == 0)
				{
					if (tmp2->content && ms_test_path(tmp2->content))
					{
						free(g_vars.exec->av[sentence][i]);
						g_vars.exec->av[sentence][i] = ms_test_path(tmp2->content);
						g_vars.exec->set_path = 1;
					}
				}
				tmp2 = tmp2->next;
			}
			if (tmp2 && tmp2->type == 2)
			{
				tmp2 = tmp2->next;
				tmp = tmp->next;
				g_vars.i = 0;
				continue;
			}
			else if (tmp->content == NULL)
				break;
		}
		g_vars.i++;
		tmp = tmp->next;
	}
}

void ms_exec_rdr_child(bool has_pipe, int redirection, int sentence, int *pipe_fd)
{
	if (!redirection && has_pipe && (dup2(pipe_fd[1], 1) == -1 || close(pipe_fd[0]) == -1 || close(pipe_fd[1]) == -1))
		exit(31);
	if (g_vars.builtin == true) // burdan built-in'e gidiyor
	{
		ms_exec_builtin(g_vars.exec->av[sentence]);
		exit(1);
	}
	else if (g_vars.exec->av_token[sentence][0] == 0 && access(g_vars.exec->av[sentence][0], 0))
	{
		errno = 127;
		printf("command not found\n");
		g_vars.exit_status = WEXITSTATUS(errno);
		exit(errno);
	}
	else
	{
		if (g_vars.heredoc_active == true)
		{
			int old_output = dup(1);
			dup2(g_vars.stdo, 1);
			close(g_vars.stdo);
			ms_run_heredoc();
			dup2(pipe_fd[1], g_vars.stdo);
			close(pipe_fd[1]);
			close(pipe_fd[0]);
			int i = -1;
			while (g_vars.heredoc->str[++i])
				printf("%s\n", g_vars.heredoc->str[i]);
			dup2(old_output, 1);
			close(old_output);
			dup2(pipe_fd[0], 0); // bu cat'in inputunu pipe yapıyor
			close(pipe_fd[1]);
			close(pipe_fd[0]);	
		}
		// dup2(g_vars.pipe_i, 0);
		execve(*g_vars.exec->av[sentence], g_vars.exec->av[sentence], g_vars.env);
		const char *errmsg = ft_strjoin("bash: ", *g_vars.exec->av[sentence]);
		perror(errmsg);
		exit(errno);
	}
}

int ms_exec_rdr_builtin(bool has_pipe, int sentence)
{
	g_vars.builtin = true;
	if (!ft_strncmp(g_vars.exec->av[sentence][0], "export", 7) && g_vars.exec->av[sentence][1] && !has_pipe)
	{
		ms_run_export(g_vars.exec->av[sentence][1]);
		return (1);
	}
	else if (!ft_strncmp(g_vars.exec->av[sentence][0], "cd", 3) && !has_pipe) // pipe yoksa her türlü cd geldi.
	{
		ms_run_cd(g_vars.exec->av[sentence]);
		return (1);
	}
	else if (!ft_strncmp(g_vars.exec->av[sentence][0], "unset", 6))
	{
		if (has_pipe)
			return (1);
		ms_run_unset(g_vars.exec->av[sentence][1]);
		return (1);
	}
	return (0);
}

int ms_exec(int sentence)
{
	int has_pipe;
	pid_t child;
	int redirection;
	int pipe_fd[2];

	g_vars.builtin = false;
	redirection = 0;
	has_pipe = 0;
	if (g_vars.exec->pipe_count > 0)
	{
		has_pipe = 1;
		g_vars.exec->pipe_count--;
	}
	if (has_pipe && pipe(pipe_fd) == -1)
		return (0);

	g_vars.retred = ms_isred_sentence(sentence); // redirection control
	if (g_vars.retred && *g_vars.retred)		 //  && g_vars.retred->type >= 3 && g_vars.retred->type <= 8 (ekstra silindi)
	{
		if (g_vars.exec->av[sentence] && ms_redirect_parse(g_vars.exec->av[sentence])) // denenmedi taslak yazıldı
			return (1);
		if (ms_redirect_manage(sentence)) // denenmedi taslak yazıldı
			return (0);
		ms_remove_redrets(sentence); // eksik
		if (!ms_node_check_builtin(g_vars.exec->av[sentence][0]) && g_vars.exec->av[sentence][0] && ms_test_path(g_vars.exec->av[sentence][0]))
			g_vars.exec->av[sentence][0] = ms_test_path(g_vars.exec->av[sentence][0]);
	}
	
// ---------------------------------------------------------------------------------------------	

	if (g_vars.exec->av_token[sentence][0] == 1) // burdan built-in'e gidiyor
		if (ms_exec_rdr_builtin(has_pipe, sentence))
			return (1);

// ---------------------------------------------------------------------------------------------

	child = fork();
	if (!child)
		ms_exec_rdr_child(has_pipe, redirection, sentence, pipe_fd);

// ---------------------------------------------------------------------------------------------
	waitpid(child, &g_vars.exit_status, 0);
	if (WIFEXITED(g_vars.exit_status))
		g_vars.exit_status = WEXITSTATUS(g_vars.exit_status);
	//  ft_putnbr_fd(g_vars.exit_status, g_vars.stdo);
	if (has_pipe && (dup2(pipe_fd[0], 0) == -1 || close(pipe_fd[0]) == -1 || close(pipe_fd[1]) == -1))
	{
		printf("[!!] dup calismadi\n");
		exit(31);
	}
	return WIFEXITED(g_vars.exit_status) && WEXITSTATUS(g_vars.exit_status);
}
