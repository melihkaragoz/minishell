/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaragoz <mkaragoz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:02:54 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/06/08 16:29:26 by mkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>

struct g_vars{};

typedef struct s_line
{
	char	*cmd;
	char	**params;
} t_line;


int		ms_strlen(char *s);
char	**ms_prepare_input(char *line);
char	*ms_prepare_cmd(char *s);
char	*ms_prepare_params(char *s);
#endif
