/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 19:08:55 by opavliuk          #+#    #+#             */
/*   Updated: 2018/08/31 19:08:57 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ls.h"

/**************** CHECK LS->HEAD **********************/
static inline void	check_head(t_info *head)
{
	struct passwd	*pwuid;
	struct group	*group;

	while (head)
	{
		group = getgrgid(head->gid);
		pwuid = getpwuid(head->uid);
//		ft_printf("===============================================\n");
//        ft_printf("file->rdev:[{white}   %u   {eoc}]\n", head->rdev);
//		ft_printf("file->blocks:[{pink}   %u   {eoc}]\n", head->blocks);
		ft_printf("file->name:[{green}  %s   {eoc}]\n", head->name_file);
//		ft_printf("file->mode:[{blue}   %s  {eoc}]\n", head->mode);
//		ft_printf("file->nlinks:[{white}   %u   {eoc}]\n", head->nlinks);
//		ft_printf("file->uid:[{white}   %u   {eoc}]\n", head->uid);
//		ft_printf("file->user:[{yellow}   %s   {eoc}]\n", pwuid->pw_name);
//		ft_printf("file->gid:[{white}   %u   {eoc}]\n", head->gid);
//		ft_printf("file->group:[{yellow}   %s   {eoc}]\n", group->gr_name);
//		ft_printf("file->size:[{red} %u   {eoc}]\n", head->size);
//		ft_printf("ctime:[ %u  ]\n", head->ctime);
//		ft_printf("file->data:[{pink}  %s  {eoc}]\n", head->data);
		head = head->next;
	}
}

static inline void	check_ls(t_ls *ls)
{
	t_dir	*dir;
	t_info 	*tmp1;
	t_info 	*tmp2;

	tmp1 = ls->files->head;
	while (tmp1)
	{
		if (tmp1->fail_file)
			ft_printf("ls: %s: No such file or directory\n", tmp1->name_file);
		tmp1 = tmp1->next;
	}

	tmp2 = ls->files->head;
	while (tmp2)
	{
		if (!tmp2->fail_file)
			ft_printf("file->name:[{green}  %s   {eoc}]\n", tmp2->name_file);
		tmp2 = tmp2->next;
	}

	dir = ls->dirs;
	while (dir)
	{
		if (!dir->close)
		{
			ft_printf("\n%s:\n", dir->name);
			ft_printf("ls->total:[{green}  %u  {eoc}]\n", dir->total);
			check_head(dir->head);
		}
		else
			ft_printf("\n%s:\nls: %s: Permission denied\n", dir->name, dir->name);
		dir = dir->next;
	}

}
/*****************************************************
******************************************************/

void 	output_for_ln(t_info *file, t_ls *ls, t_dir *dir)
{
	while (file)
	{
		if (!file->fail_file)
		{
			if (ls->flag & FLAG_N)
				ft_printf("%s%2d %-5d %-5d %*d %12.12s %s\n", file->mode,
				file->nlinks, file->uid, file->gid, dir->s_size, file->size,
				&file->data[4], file->name_file);
			else if (file->mode[0] != 'c')
				ft_printf("%s%2d %-*s %-*s %*d %12.12s %s\n",
				file->mode, file->nlinks, dir->s_name, file->pwuid->pw_name,
				dir->s_group, file->group->gr_name, dir->s_size, file->size,
				&file->data[4], file->name_file);
			else
				ft_printf("%s%2d %-*s %-*s %4d, %4d %12.12s %s\n", file->mode,
				file->nlinks, dir->s_name, file->pwuid->pw_name, dir->s_group,
				file->group->gr_name, major(file->rdev), minor(file->rdev),
				&file->data[4], file->name_file);
		}
		file = file->next;
	}
}

void	output_just(t_info *file)
{
	while (file)
	{
		if (!file->fail_file)
			ft_printf("%s\n", file->name_file);
		file = file->next;
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
	if (ls->flag & FLAG_N || ls->flag & FLAG_L)
		output_for_ln(file, ls, ls->files);
	else
		output_just(file);
}

void	output_mode(t_ls *ls)
{
	output_errnfiles(ls, ls->files->head);
//	if (ls->flag & FLAG_L || ls->flag & FLAG_N)
//		output_tn(ls->dir);

//	if (ls->flag & FLAG_R)
//		recursion();
}

int		main(int argc, char **argv)
{
	t_ls	*ls;
	int		i;

	i = 0;
	ls = (t_ls *)malloc(sizeof(t_ls));
	ft_bzero(ls, sizeof(t_ls));
	ls->files = (t_dir *)malloc(sizeof(t_dir));
	ft_bzero(ls->files, sizeof(t_dir));
	ls->files->s_size = 6;
	if (argc > 1 && argv[1][0] == '-' && ++i)
		check_flags(ls, argv[1]);
	if ((argc > 1 && !ls->flag) || (argc > 2 && ls->flag))
	{
		while (++i < argc)
			check_file_or_dir(ls, argv[i]);
	}
	else
		read_dir_info(ls, ".");

//	check_ls(ls);
//	ft_printf("======> SORT!!! <======\n");
	if (ls->files && ls->files->head)
		sort_lists(ls, ls->files);
	if (ls->dirs && ls->dirs->head)
		sort_lists(ls, ls->dirs);

	check_ls(ls);
	ft_printf("---------------------------------------\n");
//	output(ls);
	output_mode(ls);


	free_lists(ls->dirs);
//	system("leaks a.out");
	return (0);
}
