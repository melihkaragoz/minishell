/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaragoz <mkaragoz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 20:12:42 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/09/25 22:22:38 by mkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

void ms_toggle_signal(int get)
{
	if (get == 2)
		printf("CTRL+C got. [SIGINT]\n");
	else if (get == 3)
		printf("CTRL+\\ got. [SIGQUIT]\n");
	else
		printf("%d got. [UNKNOWN]\n", get);
	// val = !val;
}
