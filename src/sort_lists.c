/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_lists.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 14:30:59 by opavliuk          #+#    #+#             */
/*   Updated: 2018/09/10 14:31:01 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ls.h"

static inline void	swap_elem(t_info *a, t_info *b)
{
	(a->prev) ? a->prev->next = b : 0;
	(b->next) ? b->next->prev = a : 0;
	b->prev = a->prev;
	a->next = b->next;
	b->next = a;
	a->prev = b;
}

static inline void	sort_list_btime(t_dir *dir, t_info *first, t_info *last)
{
	while (first->next && last->prev)
	{
		if ((first->mtime < first->next->mtime) ||
			((first->mtime == first->next->mtime)
			&& (ft_strcmp(first->name_file, first->next->name_file) > 0)))
		{
			(&first->mtime != &last->mtime) ? last = dir->last_file->prev : 0;
			(&dir->head->size == &first->size) ? dir->head = first->next : 0;
			swap_elem(first, first->next);
			first = dir->head;
			continue ;
		}
		if ((last->mtime < last->next->mtime) ||
			((last->mtime == last->next->mtime)
			&& (ft_strcmp(last->name_file, last->next->name_file) > 0)))
		{
			(&dir->last_file->size == &last->next->size)
			? dir->last_file = last : 0;
			swap_elem(last, last->next);
			last = dir->last_file->prev;
			continue ;
		}
		first = first->next;
		last = last->prev;
	}
}

static inline void	sort_list_bname(t_dir *dir, t_info *first, t_info *last)
{
	while (first->next && last->prev)
	{
		if (ft_strcmp(first->name_file, first->next->name_file) > 0)
		{
			(&first->name_file != &last->name_file)
			? last = dir->last_file->prev : 0;
			(&dir->head->size == &first->size) ? dir->head = first->next : 0;
			swap_elem(first, first->next);
			first = dir->head;
			continue ;
		}
		if (ft_strcmp(last->name_file, last->next->name_file) > 0)
		{
			(&dir->last_file->size == &last->next->size)
			? dir->last_file = last : 0;
			swap_elem(last, last->next);
			last = dir->last_file->prev;
			continue ;
		}
		first = first->next;
		last = last->prev;
	}
}

void				sort_lists(t_ls *ls, t_dir *dir)
{
	if (ls->flag & FLAG_T)
		sort_list_btime(dir, dir->head, dir->last_file->prev);
	else
		sort_list_bname(dir, dir->head, dir->last_file->prev);
}

void 				sort_argv(char **argv)
{
	char 	*tmp;
	int 	i;

	i = 1;
	while (argv[i] && argv[i + 1])
	{
		if (ft_strcmp(argv[i], argv[i + 1]) > 0)
		{
			tmp = argv[i];
			argv[i] = argv[i + 1];
			argv[i + 1] = tmp;
			i = 0;
		}
		++i;
	}
}
