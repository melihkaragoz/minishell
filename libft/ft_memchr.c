/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaragoz <mkaragoz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 04:33:02 by mkaragoz          #+#    #+#             */
/*   Updated: 2022/11/01 02:47:55 by mkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			cur;

	str = (unsigned char *)s;
	cur = 0;
	while (cur < n)
	{
		if (str[cur] == (unsigned char)c)
			return ((void *)&str[cur]);
		cur++;
	}
	return (NULL);
}
