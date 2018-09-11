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

void	output_ln(t_info *file, t_ls *ls, t_dir *dir)
{
	while (file)
	{
		if (!file->fail_file)
		{
			if (ls->flag & FLAG_N)
				ft_printf("%s %*d %-5d %-5d %*d %12.12s %s\n", file->mode,
				dir->s_link, file->nlinks, file->uid, file->gid, dir->s_size,
				file->size, &file->data[4], file->name_file);
			else if (file->mode[0] == 'c' || file->mode[0] == 'b')
				ft_printf("%s %*d %-*s %-*s %3d, %3d %12.12s %s\n", file->mode,
				dir->s_link, file->nlinks, dir->s_name, file->name_user,
				dir->s_group, file->name_group, major(file->rdev),
				minor(file->rdev), &file->data[4], file->name_file);
			else
				ft_printf("%s %*d %-*s %-*s %*d %12.12s %s\n", file->mode,
				dir->s_link, file->nlinks, dir->s_name, file->name_user,
				dir->s_group, file->name_group, dir->s_size, file->size,
				&file->data[4], file->name_file);
		}
		file = (ls->flag & FLAG_RR) ? file->prev : file->next;
	}
}

void	output_just(t_dir *dir, char flag)
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

void	output_errnfiles(t_ls *ls, t_info *file)
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
