/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anargul <anargul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:39:37 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/10/14 10:49:37 by anargul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

t_return_red **ms_isred_sentence(int sentence)
{
	t_return_red **returnred;
	int i;
	int j;
	int a;

	i = -1;
	a = 0;
	j = -1;
	while (g_vars.exec->av[sentence][++i])
		if (g_vars.exec->av[sentence][i] && (g_vars.exec->av_token[sentence][i] >= 3 && g_vars.exec->av_token[sentence][i] <= 8))
			a++;
	g_vars.exec->red_count = a;
	if (a == 0)
		return (0);
	returnred =ft_malloc(sizeof(t_return_red *) * (a + 1));
	while (++j < a) // for var [melih] while'a cevirdim
		returnred[j] =ft_malloc(sizeof(t_return_red *));
	i = -1;
	j = 0;
	while (g_vars.exec->av[sentence][++i])
	{
		if (!a)
		{
			returnred[g_vars.exec->red_count] = NULL;
			return (returnred);
		}
		if (g_vars.exec->av_token[sentence][i] >= 3 && g_vars.exec->av_token[sentence][i] <= 8 && a--) // [melih] a-- yi buraya aldim
		{
			returnred[j]->index = i;
			returnred[j]->type = g_vars.exec->av_token[sentence][i];
			j++;
		}
	}
	return (returnred);
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

	str =ft_malloc(sizeof(char *) * (end - start + 2));
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
		//free(g_vars.exec->av[sentence][i]);
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
			g_vars.heredoc_active = 1;
			if (ms_set_heredoc(g_vars.exec->av[sentence], g_vars.retred[i]->index))
				break; // return (1);
		}
	}
	// if (hrdc == true)
	// 	ms_run_heredoc();

	g_vars.heredoc_str = g_vars.heredoc_str_head;
	// while (g_vars.heredoc_str->str)
	// {
	// 	printf("%s\n", g_vars.heredoc_str->str); // bunu pipe'a yaz sonra obur uctan okuyalim veya cat'e falan gonder
	// 	g_vars.heredoc_str = g_vars.heredoc_str->next;
	// }
	return (0);
}
