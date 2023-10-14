/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anargul <anargul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 20:12:42 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/10/14 18:02:31 by anargul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

void ms_toggle_signal(int get)
{
	if (get == 3)
	{
		write(1, "\033[2D", 3);
		write(1, "  ", 2);
		write(1, "\033[2D", 3);
		return;
	}
	write(1, "\033[A", 3);
	ioctl(0, TIOCSTI, "\n");
	g_vars.rm = 1;
}

void	ms_signal_helper(int get)
{
	(void)get;
	if (g_vars.quit_flag == 1)
	{
		write(1, "\033[2D", 4);
		write(1, "  ", 2);
		write(1, "\033[2D", 4);
		ioctl(-1, TIOCSTI, "\n");
		g_vars.quit_flag = 0;
	}
	g_vars.quit_flag = 1;
}

void ms_exit(char *msg, int stat)
{
	if (msg && *msg)
		printf("%s\n", msg);
		free(g_vars.line);
	// ms_detective_leak();
	if (stat == 1) // ctrl-d gelme durumu
	{
		g_vars.gc_iterator = g_vars.gc_head;
		free(g_vars.gc_iterator->content);
		// for (; g_vars.gc_iterator->content; g_vars.gc_iterator = g_vars.gc_iterator->next)
		// {
		// 	if ((char *)g_vars.gc_iterator->content)
		// 		free(g_vars.gc_iterator->content);
		// }
		printf("\033[A\n%sexit\n", g_vars.prompt);
		exit(0);
	}
	exit(stat);
}
