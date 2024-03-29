/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anargul <anargul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 00:37:21 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/10/14 10:49:37 by anargul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int			endl;
	int			c;
	static char	*str;
	char		*tmp_str;

	endl = 1;
	str = ft_malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!str || fd < 0 || BUFFER_SIZE <= 0)
	{
		//free(str);
		return (0);
	}
	tmp_str = str;
	while (endl)
	{
		c = read(fd, str, 1);
		if (c <= 0)
			break;
		else if (c == -1 && endl == 1)
			return (0);
		if (*(str) != '\n' && endl < BUFFER_SIZE)
			endl++;
		else
			endl = 0;
		str++;
	}
	if (!tmp_str)
		return (0);
	if (*(--str) != '\n')
		*(str) = '\n';
	return (tmp_str);
}
