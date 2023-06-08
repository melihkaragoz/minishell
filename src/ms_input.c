/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaragoz <mkaragoz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:23:29 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/06/08 16:45:44 by mkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ms_prepare_input(char *line)
{
	char	*cmd = ms_prepare_cmd(line);
	// char	*params = ms_prepare_params(line);
	printf("cmd = %s\n", cmd);
	return (0);
}

char	*ms_prepare_cmd(char *s)
{
	char	*cmd;

	if (ft_strchr(s, ' '))
	{
		cmd = malloc(sizeof(char) * (ft_strchr(s, ' ') - s + 2));
		ft_strlcpy(cmd, s, ft_strchr(s,' ') - s + 1);
	}
	else
		cmd = NULL;
	return (cmd);
}

char	*ms_prepare_params(char *s);
