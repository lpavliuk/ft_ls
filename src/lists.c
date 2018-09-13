/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 18:54:23 by opavliuk          #+#    #+#             */
/*   Updated: 2018/09/05 18:54:24 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ls.h"

t_dir	*new_dir(t_ls *ls, const char *name)
{
	if (!ls->dirs)
	{
		ls->dirs = (t_dir *)malloc(sizeof(t_dir));
		ft_bzero(ls->dirs, sizeof(t_dir));
		(ls->dirs)->name = ft_strdup(name);
		ls->dirs->prev = NULL;
		ls->last_dir = ls->dirs;
		return (ls->dirs);
	}
	else
	{
		ls->last_dir->next = (t_dir *)malloc(sizeof(t_dir));
		ft_bzero(ls->last_dir->next, sizeof(t_dir));
		ls->last_dir->next->name = ft_strdup(name);
		ls->last_dir->next->prev = ls->last_dir;
		ls->last_dir = ls->last_dir->next;
		return (ls->last_dir);
	}
}

t_info	*new_file(t_dir *dir)
{
	if (!dir->head)
	{
		dir->head = (t_info *)malloc(sizeof(t_info));
		ft_bzero(dir->head, sizeof(t_info));
		dir->last_file = dir->head;
		dir->last_file->prev = NULL;
		return (dir->head);
	}
	else
	{
		dir->last_file->next = (t_info *)malloc(sizeof(t_info));
		ft_bzero(dir->last_file->next, sizeof(t_info));
		dir->last_file->next->prev = dir->last_file;
		dir->last_file = dir->last_file->next;
		return (dir->last_file);
	}
}
