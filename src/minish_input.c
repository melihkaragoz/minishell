/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaragoz <mkaragoz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:23:29 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/08/13 23:18:46 by mkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_get_cmd(void)
{
	char	*cmd;
	char	sp;
	int		cmd_len;
	char	*left_st;

	if (g_vars.line)
	{
		if(ft_strchr(g_vars.line, ' '))
			sp = ' ';
		else
			sp = '\0';
		cmd_len = (ft_strchr(g_vars.line, sp) - g_vars.line + 2);
		cmd = malloc(sizeof(char) * cmd_len);
		ft_strlcpy(cmd, g_vars.line, ft_strchr(g_vars.line, sp) - g_vars.line + 1);
		g_vars.left = malloc(sizeof(char) * ft_strlen(g_vars.line) - cmd_len + 1);
		left_st = ft_strchr(g_vars.line, sp);
		ft_strlcpy(g_vars.left, left_st, ft_strchr(g_vars.line, 0) - left_st + 1);
		printf("left: %s\n", g_vars.left);
	}
	else
		cmd = NULL;
	return (cmd);
}
