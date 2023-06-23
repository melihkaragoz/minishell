/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaragoz <mkaragoz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:23:29 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/06/23 15:16:49 by mkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_prepare_input(t_line *tl)
{
	tl->cmd		= ms_prepare_cmd(tl);
	//tl->params	= ms_prepare_params(tl);
	printf("cmd = %s\n", tl->cmd);
}

char	*ms_prepare_cmd(t_line *tl)
{
	char	*cmd;

	char *s = tl->line;
	if (*s)
	{
		if(ft_strchr(s, ' '))
		{
			cmd = malloc(sizeof(char) * (ft_strchr(s, ' ') - s + 2));
			ft_strlcpy(cmd, s, ft_strchr(s,' ') - s + 1);
		}
		else
		{
			cmd = malloc(sizeof(char) * (ft_strchr(s, '\0') - s + 2));
			ft_strlcpy(cmd, s, ft_strchr(s,'\0') - s + 1);
		}
	}
	else
		cmd = NULL;
	return (cmd);
}

char	**ms_prepare_params(t_line *tl);
