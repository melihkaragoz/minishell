/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anargul <anargul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:16:50 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/10/14 11:11:29 by anargul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	word_counter(const char *str, char c)
{
	int	count;
	int	i;
	int	flag;

	count = 0;
	i = 0;
	flag = 1;
	while (str[i])
	{
		if (str[i] != c && flag == 1)
		{
			count++;
			flag = 0;
		}
		else if (str[i] == c)
			flag = 1;
		i++;
	}
	return (count);
}

int	word_len(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] == c)
		i++;
	while (str[i] != c && str[i])
	{
		i++;
		count++;
	}
	return (count);
}

char	*stringer(const char *src, char c)
{
	char	*ret;
	int		i;

	ret =ft_malloc(sizeof(char) * word_len(src, c) + 1);
	i = 0;
	while (*src && *src != c)
	{
		ret[i] = *(src++);
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	**ft_split(const char *s, char c)
{
	char	**result;
	size_t	size;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	size = word_counter(s, c);
	result = ft_malloc(sizeof(char *) * (size + 1));
	if (!result)
		return (0);
	i = 0;
	j = 0;
	while (j < size && s[i])
	{
		while (s[i] == c)
			i++;
		result[j] = stringer(&s[i], c);
		while (s[i] != c && s[i])
			i++;
		j++;
	}
	result[j] = NULL;
	return (result);
}
