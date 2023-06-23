/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaragoz <mkaragoz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:54:08 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/06/23 15:19:08 by mkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_exec(t_line *tl)
{
	// path value'su alınıp ':'e göre splitlenecek ve döngü içinde indexler tek tek access'ten geçerli bir return value alınana kadar çalıştırılacak.
	int ev = -1;
	int rv = access(tl->cmd, F_OK);
	char *prm[] = {"" ,NULL};
	printf("%d\n",rv);
	if(!rv)
		ev = execv(tl->cmd, prm);
	return (ev);
}


