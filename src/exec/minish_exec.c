/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anargul <anargul@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:54:08 by mkaragoz          #+#    #+#             */
/*   Updated: 2023/10/14 10:38:00 by anargul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/minishell.h"

t_gc *new_gc()
{
    t_gc *gc = malloc(sizeof(t_gc));
    gc->content = NULL;
    gc->next = NULL;
    return (gc);
}

void add_gc_element(void *el)
{
    g_vars.gc_iterator->content = el;
    g_vars.gc_iterator->next = new_gc();
    g_vars.gc_iterator = g_vars.gc_iterator->next;
}

void ms_detective_leak(void)
{
    system("leaks minishell");
    getchar();
}

void *ft_malloc(size_t num)
{
    void    *ptr;

    ptr = malloc(num);
    add_gc_element(ptr);
    return (ptr);
}