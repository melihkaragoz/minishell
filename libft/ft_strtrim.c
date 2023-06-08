/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaragoz <mkaragoz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 22:30:21 by mkaragoz          #+#    #+#             */
/*   Updated: 2022/11/01 15:57:59 by mkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		l;
	char	*result;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	l = ft_strlen(s1) - 1;
	while (l && ft_strchr(set, s1[l]))
		l--;
	result = ft_substr(s1, 0, l + 1);
	if (result == NULL)
		return (0);
	return (result);
}
