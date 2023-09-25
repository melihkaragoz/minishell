/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaragoz <mkaragoz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 02:20:42 by mkaragoz          #+#    #+#             */
/*   Updated: 2022/10/28 04:45:16 by mkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*t;

	i = 0;
	if (!lst)
		return (0);
	t = lst;
	while (t)
	{
		t = t->next;
		i++;
	}
	return (i);
}
