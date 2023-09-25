/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaragoz <mkaragoz@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 02:14:42 by mkaragoz          #+#    #+#             */
/*   Updated: 2022/11/11 00:07:57 by mkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
#ifndef BUFFER_SIZE // .h dosyasina eklenecek.
#define BUFFER_SIZE 42
#endif
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
char	*get_next_line(int fd);
#endif
