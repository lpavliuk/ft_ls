/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 16:38:37 by opavliuk          #+#    #+#             */
/*   Updated: 2018/09/14 16:38:38 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ls.h>

static inline void	work_with_dir(t_ls *ls, t_dir *direct)
{
	if (direct->head)
		sort_lists(ls, direct);
	if (direct->close)
		ft_error(direct->name, 1);
	else if ((ls->flag & FLAG_N || ls->flag & FLAG_L) && direct->head)
		ft_printf("total %d\n", direct->total);
	if (direct->head && ls->flag & FLAG_RR &&
		(ls->flag & FLAG_N || ls->flag & FLAG_L))
		output_ln(direct->last_file, ls, direct);
	else if (ls->flag & FLAG_N || ls->flag & FLAG_L)
		output_ln(direct->head, ls, direct);
	else
		output_just(direct, ls->flag);
}

static inline void	info_dir(t_ls *ls, t_dir *direct)
{
	t_info	*file;
	t_dir	*dir;

	if (&ls->dirs->name != &direct->name)
		ft_printf("%s:\n", direct->name);
	work_with_dir(ls, direct);
	file = (ls->flag & FLAG_RR) ? direct->last_file : direct->head;
	while (file)
	{
		if (file->mode[0] == 'd' && ft_strcmp(file->name_file, ".") != 0
			&& ft_strcmp(file->name_file, "..") != 0)
		{
			read_dir_info(ls, file->pwd);
			dir = ls->last_dir;
			write(1, "\n", 1);
			info_dir(ls, dir);
		}
		file = (ls->flag & FLAG_RR) ? file->prev : file->next;
	}
}

void				recursion(t_ls *ls, t_dir *dir)
{
	t_dir *last;

	last = ls->last_dir;
	while (dir)
	{
		info_dir(ls, dir);
		if (&last->name == &dir->name)
			break ;
		write(1, "\n", 1);
		dir = dir->next;
	}
}
