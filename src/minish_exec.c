/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anargul <anargul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:54:08 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/09/10 02:34:07 by anargul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ms_check_env(t_token *org_token)
{
	t_token *token;
	int quote;
	int dl_sign;
	int i;

	// printf("[!] the node's content is: %s\n", token->content);
	token = org_token;
	i = -1;
	quote = 0;
	dl_sign = 0;
	// printf("char: %c, quote: %d, end: %d, dollar: %d", token->content[i], quote, quote_end, dl_sign);
	while ((token->content) && *(token->content) && token->content[++i])
	{
		if (quote == 2 && token->content[i] == '$' && ++dl_sign)
		{
			ms_put_env(token, &i);
			dl_sign = 0;
			continue;
		}
		else if (token->content[i] == '\'')
		{
			if (quote == 1)
			{
				quote = 0;
			}
			else if (quote == 0)
				quote = 1;
		}
		else if (token->content[i] == '\"')
		{
			if (quote == 2)
			{
				quote = 0;
			}
			else if (quote == 0)
				quote = 2;
		}
		// printf("char: %c, quote: %d, end: %d, dollar: %d", token->content[i], quote, quote_end, dl_sign);
		// getchar();
	}
	if (!dl_sign)
		return;
}

void ms_put_env(t_token *token, int *i)
{
	char *adr;
	char *tmp;
	char *t_tmp;
	char *t_first;
	char *t_last;

	adr = &(token->content[*i]);
	*i = 1;
	while (ft_isalnum(adr[*i]))
		(*i)++;
	tmp = ft_substr(adr, 1, *i - 1);
	t_first = ft_substr(token->content, 0, adr - (token->content));
	t_last = ft_substr(token->content, (adr + *i) - (token->content), ft_strlen(adr + *i));
	// printf("[!] token is: %s\n", tmp);
	// printf("[!] value is: %s\n", getenv(tmp));
	// printf("[!] first part of content: %s\n", t_first);
	// printf("[!] last part of content: %s\n", t_last);
	if (getenv(tmp))
		t_tmp = ft_strjoin(t_first, getenv(tmp));
	else
		t_tmp = ft_strjoin(t_first, "");
	t_tmp = ft_strjoin(t_tmp, t_last);
	free(token->content);
	token->content = t_tmp;
	free(t_first);
	free(t_last);
	if (getenv(tmp))
		*i += ft_strlen(getenv(tmp)) + ft_strlen(tmp);
	free(tmp);
}

// int ms_exec(void)
// {
// 	int ev = -1;
// 	int pid;
// 	char *prm[] = {"", NULL};

// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		execve(g_vars.v_path, prm, g_vars.paths);
// 		exit(127);
// 	}
// 	waitpid(pid, NULL, 0);
// 	return (ev);
// }
