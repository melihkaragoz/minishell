/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaragoz <mkaragoz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:32:37 by mkaragoz          #+#    #+#             */
/*   Updated: 2022/10/28 10:05:59 by mkaragoz         ###   ########.fr       */
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
