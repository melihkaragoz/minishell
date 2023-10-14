/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anargul <anargul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:32:37 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/10/14 10:26:52 by anargul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void		*np;
	size_t		i;

	i = 0;
	np = (void *)malloc((count * size) * sizeof(char));
	((char *)np)[0] = 0;
	if ((count && size) && (count < SIZE_MAX && size < SIZE_MAX))
	{
		while (i < count * size)
			((char *) np)[i++] = 0;
	}
	return (np);
}
