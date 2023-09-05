/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaragoz <mkaragoz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:54:08 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/09/05 22:20:39 by mkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ms_put_env(t_token *token)
{
	char *adr;
	char *tmp;
	char *t_tmp;
	char *t_first;
	char *t_last;
	int quote;
	int quote_end;
	int dl_sign;
	int i;

	// printf("[!] the node's content is: %s\n", token->content);
	i = -1;
	quote = 0;
	quote_end = 0;
	dl_sign = 0;
	// printf("char: %c, quote: %d, end: %d, dollar: %d", token->content[i], quote, quote_end, dl_sign);
	while ((token->content) && *(token->content) && token->content[++i])
	{
		if (quote == 2 && token->content[i] == '$' && dl_sign++)
			break;
		else if (token->content[i] == '\'')
		{
			if (quote == 1)
			{
				quote_end = 1;
				quote = 0;
			}
			else if (quote == 0)
				quote = 1;
		}
		else if (token->content[i] == '\"')
		{
			if (quote == 2)
			{
				quote_end = 1;
				quote = 0;
			}
			else if (quote == 0)
				quote = 2;
		}
		// printf("char: %c, quote: %d, end: %d, dollar: %d\n", token->content[i], quote, quote_end, dl_sign);
		// getchar();
	}
	if (!dl_sign)
		return;
	i = 0;
	adr = ft_strchr(token->content, '$');
	if ((!((*(token->content))) || !adr) || i++)
		return;
	while (ft_isalnum(adr[i]))
		i++;
	// printf("%c, %d\n", *(adr + i), ft_isalnum(*(adr + i)));
	tmp = ft_substr(adr, 1, i - 1);
	t_first = ft_substr(token->content, 0, adr - (token->content));
	t_last = ft_substr(token->content, (adr + i) - (token->content), ft_strlen(adr + i));
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
}

int ms_exec(void)
{
	int ev = -1;
	int pid;
	char *prm[] = {"", NULL};

	pid = fork();
	if (pid == 0)
	{
		execve(g_vars.v_path, prm, g_vars.paths);
		exit(127);
	}
	waitpid(pid, NULL, 0);
	return (ev);
}
