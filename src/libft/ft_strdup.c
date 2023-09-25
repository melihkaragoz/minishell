/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaragoz <mkaragoz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 04:45:07 by mkaragoz          #+#    #+#             */
/*   Updated: 2022/10/25 03:35:12 by mkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*c;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	c = (char *)malloc(ft_strlen(str) + 1);
	if (!c)
		return (NULL);
	while (str[i])
	{
		c[i] = str[i];
		i++;
	}
	c[i] = 0;
	return (c);
}
