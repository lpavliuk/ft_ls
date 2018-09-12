/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 19:07:21 by opavliuk          #+#    #+#             */
/*   Updated: 2018/09/11 19:07:22 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ls.h"

void				output_ln(t_info *file, t_ls *ls, t_dir *dir)
{
	while (file)
	{
		if (!file->fail_file)
		{
			if (ls->flag & FLAG_N)
				ft_printf("%s %*d %-5d %-5d %*d %-12.12s %s\n", file->mode,
				dir->s_link, file->nlinks, file->uid, file->gid, dir->s_size,
				file->size, &file->data[4], file->name_file);
			else if (file->mode[0] == 'c' || file->mode[0] == 'b')
				ft_printf("%s %*d %-*s %-*s %3d, %3d %-12.12s %s\n", file->mode,
				dir->s_link, file->nlinks, dir->s_name, file->name_user,
				dir->s_group, file->name_group, major(file->rdev),
				minor(file->rdev), &file->data[4], file->name_file);
			else
				ft_printf("%s %*d %-*s %-*s %*d %-12.12s %s\n", file->mode,
				dir->s_link, file->nlinks, dir->s_name, file->name_user,
				dir->s_group, file->name_group, dir->s_size, file->size,
				&file->data[4], file->name_file);
		}
		file = (ls->flag & FLAG_RR) ? file->prev : file->next;
	}
}

void				output_just(t_dir *dir, char flag)
{
	t_info *tmp;

	tmp = (flag & FLAG_RR) ? dir->last_file : dir->head;
	while (tmp)
	{
		if (!tmp->fail_file)
			ft_printf("%s\n", tmp->name_file);
		tmp = (flag & FLAG_RR) ? tmp->prev : tmp->next;
	}
}

static inline void	output_errnfiles(t_ls *ls, t_info *file)
{
	t_info *tmp;

	tmp = file;
	while (tmp)
	{
		if (tmp->fail_file)
			ft_printf("ls: %s: No such file or directory\n", tmp->name_file);
		tmp = tmp->next;
	}
	if ((ls->flag & FLAG_N || ls->flag & FLAG_L) && ls->flag & FLAG_RR)
		output_ln(ls->files->last_file, ls, ls->files);
	else if (ls->flag & FLAG_N || ls->flag & FLAG_L)
		output_ln(file, ls, ls->files);
	else
		output_just(ls->files, ls->flag);
}

void				output_for(t_ls *ls, t_dir **next)
{
	while (ls->dirs)
	{
		if (ls->dirs->head)
			sort_lists(ls, ls->dirs);
		if (*next)
			ft_printf("%s:\n", ls->dirs->name);
		if (ls->dirs->close)
			ft_printf("ls: %s: Permission denied\n", ls->dirs->name);
		else if (ls->flag & FLAG_N || ls->flag & FLAG_L)
			ft_printf("total %d\n", ls->dirs->total);
		if (ls->dirs->head && ls->flag & FLAG_RR &&
			(ls->flag & FLAG_N || ls->flag & FLAG_L))
			output_ln(ls->dirs->last_file, ls, ls->dirs);
		else if (ls->flag & FLAG_N || ls->flag & FLAG_L)
			output_ln(ls->dirs->head, ls, ls->dirs);
		else
			output_just(ls->dirs, ls->flag);
		if (ls->dirs->next)
			write(1, "\n", 1);
		ls->dirs = (ls->flag & FLAG_RR) ? ls->dirs->prev : ls->dirs->next;
	}
}

void				output_mode(t_ls *ls)
{
//	t_dir *tmp;

	if (ls->files->head)
		output_errnfiles(ls, ls->files->head);
	if (ls->files->head && ls->dirs)
		write(1, "\n", 1);
	output_for(ls, &ls->dirs->next);
//	else
//	{
//		tmp = (ls->flag & FLAG_RR) ? ls->dirs->last_file : ls->dirs->head;
//		while (tmp)
//		{
//			if (tmp->head)
//				sort_lists(ls, tmp);
//			output_just(tmp, ls->flag);
//			ls->dirs = ls->dirs->next;
//		}
//	}
//	if (ls->flag & FLAG_R)
//		recursion();
}
