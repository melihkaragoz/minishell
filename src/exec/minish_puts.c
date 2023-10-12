/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_puts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaragoz <mkaragoz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:56:21 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/10/12 13:57:48 by mkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

void ms_check_env(t_token *org_token)
{
	t_token *token;
	int quote;
	int dl_sign;
	int i;

	token = org_token;
	i = -1;
	quote = 0;
	dl_sign = 0;
	while ((token->content) && token->content[++i])
	{
		if ((quote == 2 || quote == 0) && token->content[i] == '$' && (ft_isalnum(token->content[i + 1]) || token->content[i + 1] == '$' || token->content[i + 1] == '?') && ++dl_sign)
		{
			if (token->content[i + 1] == '$')
				ms_put_dollar(token, &i);
			else if (token->content[i + 1] == '?')
				ms_put_status(token, &i);
			else if (token->content[i + 1] == '0')
				ms_put_program_name(token, &i);
			else
				ms_put_env(token, &i);
			dl_sign = 0;
			continue;
		}
		else if (token->content[i] == '\'')
		{
			if (quote == 1)
				quote = 0;
			else if (quote == 0)
				quote = 1;
		}
		else if (token->content[i] == '\"')
		{
			if (quote == 2)
				quote = 0;
			else if (quote == 0)
				quote = 2;
		}
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
	char *val;

	adr = &(token->content[*i]);
	*i = 1;
	while (ft_isalnum(adr[*i]))
		(*i)++;
	tmp = ft_substr(adr, 1, *i - 1);
	t_first = ft_substr(token->content, 0, adr - (token->content));
	t_last = ft_substr(token->content, (adr + *i) - (token->content), ft_strlen(adr + *i));
	val = ms_getenv(tmp);
	if (val)
		t_tmp = ft_strjoin(t_first, val);
	else
		t_tmp = ft_strjoin(t_first, "");
	t_tmp = ft_strjoin(t_tmp, t_last);
	free(token->content);
	token->content = t_tmp;
	free(t_first);
	free(t_last);
	if (val)
		*i += ft_strlen(val) - ft_strlen(tmp) - 2;
	free(val);
	free(tmp);
}


void ms_put_dollar(t_token *token, int *i)
{
	char	*pid;
	char *tmp;
	char *t_first;
	char *t_last;

	pid = ft_itoa(getpid());
	t_first = ft_substr(token->content, 0, *i);
	t_last = ft_substr(token->content, *i + 2, ft_strlen(token->content) - (*i));
	tmp = ft_strjoin(t_first, pid);
	free(t_first);
	free(pid);
	token->content = ft_strjoin(tmp, t_last);
	free(tmp);
	free(t_last);
}

void ms_put_status(t_token *token, int *i)
{
	char *tmp;
	char *t_first;
	char *t_last;
	char *ms_itoa;

	ms_itoa = ft_itoa(g_vars.exit_status);
	t_first = ft_substr(token->content, 0, *i);
	t_last = ft_substr(token->content, *i + 2, ft_strlen(token->content) - (*i));
	tmp = ft_strjoin(t_first, ms_itoa);
	token->content = ft_strjoin(tmp, t_last);
	free(t_first);
	free(ms_itoa);
	free(tmp);
	free(t_last);
}

void ms_put_program_name(t_token *token, int *i)
{
	char *tmp;
	char *t_first;
	char *t_last;

	t_first = ft_substr(token->content, 0, *i);
	t_last = ft_substr(token->content, *i + 2, ft_strlen(token->content) - (*i));
	(tmp = ft_strjoin(t_first, "minishell")) && (token->content = ft_strjoin(tmp, t_last));
	free(t_first);
	free(tmp);
	free(t_last);
}
