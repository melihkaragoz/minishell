/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaragoz <mkaragoz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 22:26:51 by mkaragoz          #+#    #+#             */
/*   Updated: 2022/10/28 04:38:04 by mkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dlen)
{
	size_t	slen;
	size_t	i;

	if (!src || !dst)
		return (0);
	slen = ft_strlen(src);
	i = 0;
	if (dlen != 0)
	{
		while (src[i] != '\0' && i < (dlen - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (slen);
}
