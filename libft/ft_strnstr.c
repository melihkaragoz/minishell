/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaragoz <mkaragoz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 04:35:11 by mkaragoz          #+#    #+#             */
/*   Updated: 2022/10/28 04:42:53 by mkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *tofind, size_t n)
{
	size_t	len_td;

	len_td = ft_strlen(tofind);
	if (!*tofind)
		return ((char *)str);
	while (*str && n-- >= len_td)
	{
		if (*str == *tofind && ft_memcmp(str, tofind, len_td) == 0)
			return ((char *)str);
		str++;
	}
	return (NULL);
}
