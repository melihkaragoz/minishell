/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaragoz <mkaragoz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 20:12:42 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/09/26 02:00:50 by mkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

void ms_toggle_signal(int get)
{
	(void)get;
	write(1, "\033[A", 3);
	ioctl(0, TIOCSTI, "\n");
	g_vars.rm = 1;
}

void ms_exit(char *msg, int stat)
{
	if (msg && *msg)
		printf("%s\n", msg);
	if (stat == 1) // ctrl-d gelme durumu
	{
		write(1, "\033[A\n", 4);
		write(1, "\x1b[38;5;129mminishell$ \x1b[0mexit\n", 31);
		exit(0);
	}
	exit(stat);
}
