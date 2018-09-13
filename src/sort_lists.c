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

static inline void	sort_list_btime(t_dir *dir)
{
	char	flag;
	t_info	*tmp;

	while (1)
	{
		flag = 1;
		tmp = dir->head;
		while (tmp->next)
		{
			if ((tmp->mtime < tmp->next->mtime) ||
				((tmp->mtime == tmp->next->mtime)
				 && (ft_strcmp(tmp->name_file, tmp->next->name_file) > 0)))
			{
				(&dir->head->size == &tmp->size) ? dir->head = tmp->next : 0;
				swap_elem(tmp, tmp->next);
				flag = 0;
				break ;
			}
			tmp = tmp->next;
		}
		if (flag)
			break ;
	}
}

static inline void	sort_list_bname(t_dir *dir)
{
	char	flag;
	t_info	*tmp;

	while (1)
	{
		flag = 1;
		tmp = dir->head;
		while (tmp->next)
		{
			if (ft_strcmp(tmp->name_file, tmp->next->name_file) > 0)
			{
				(&dir->head->size == &tmp->size) ? dir->head = tmp->next : 0;
				swap_elem(tmp, tmp->next);
				flag = 0;
				break ;
			}
			tmp = tmp->next;
		}
		if (flag)
			break ;
	}
}

void				sort_lists(t_ls *ls, t_dir *dir)
{
	if (ls->flag & FLAG_T)
		sort_list_btime(dir);
	else
		sort_list_bname(dir);
}
