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

static inline int	ft_strlen_list(t_info *list)
{
	int i;

	i = 0;
	while (list)
	{
		list = list->next;
		++i;
	}
	return (i);
}

static inline void	swap_elem(t_info *a, t_info *b)
{
	(a->prev) ? a->prev->next = b : 0;
	(b->next) ? b->next->prev = a : 0;
	b->prev = a->prev;
	a->next = b->next;
	b->next = a;
	a->prev = b;
}

static inline void	sort_list_btime(t_dir *dir, t_info *tmp)
{
	int i;
	int j;
	int len;

	i = -1;
	len = ft_strlen_list(dir->head) - 1;
	while (++i < len - 1)
	{
		j = -1;
		tmp = dir->head;
		while (tmp->next && ++j < len - i - 1)
		{
			if ((tmp->mtime < tmp->next->mtime) ||
				((tmp->mtime == tmp->next->mtime)
				&& (ft_strcmp(tmp->name_file, tmp->next->name_file) > 0)))
			{
				(&dir->head->size == &tmp->size) ? dir->head = tmp->next : 0;
				(&dir->last_file->size == &tmp->next->size)
				? dir->last_file = tmp : 0;
				swap_elem(tmp, tmp->next);
			}
			if (tmp->next)
				tmp = tmp->next;
		}
	}
}

static inline void	sort_list_bname(t_dir *dir, t_info *tmp)
{
	int i;
	int j;
	int len;

	i = -1;
	len = ft_strlen_list(dir->head) - 1;
	while (++i < len - 1)
	{
		j = -1;
		tmp = dir->head;
		while (tmp->next && ++j < len - i - 1)
		{
			if (ft_strcmp(tmp->name_file, tmp->next->name_file) > 0)
			{
				(&dir->head->size == &tmp->size) ? dir->head = tmp->next : 0;
				(&dir->last_file->size == &tmp->next->size)
				? dir->last_file = tmp : 0;
				swap_elem(tmp, tmp->next);
			}
			if (tmp->next)
				tmp = tmp->next;
		}
	}
}

void				sort_lists(t_ls *ls, t_dir *dir)
{
	if (ls->flag & FLAG_T)
		sort_list_btime(dir, dir->head);
	else
		sort_list_bname(dir, dir->head);
}
