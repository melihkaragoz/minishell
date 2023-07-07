/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaragoz <mkaragoz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:23:29 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/07/07 23:33:36 by mkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_get_cmd(void)
{
	char	*cmd;
	char	sp;

	if (g_vars.line)
	{
		if(ft_strchr(g_vars.line, ' '))
			sp = ' ';
		else
			sp = '\0';
		cmd = malloc(sizeof(char) * (ft_strchr(g_vars.line, sp) - g_vars.line + 2));
		ft_strlcpy(cmd, g_vars.line, ft_strchr(g_vars.line, sp) - g_vars.line + 1);
	}
	else
		cmd = NULL;
	return (cmd);
}
