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
	t_dir	*tmp;

	tmp = ls->files;
	while (tmp)
	{
		while (tmp->head)
		{
			if (tmp->head->fail_file)
				ft_printf("ls: %s: No such file or directory\n", tmp->head->name_file);
			tmp->head = tmp->head->next;
		}
		tmp = tmp->next;
	}

	tmp = ls->files;
	while (tmp)
	{
		while (tmp->head)
		{
			if (!tmp->head->fail_file)
				ft_printf("file->name:[{green}  %s   {eoc}]\n", tmp->head->name_file);
			tmp->head = tmp->head->next;
		}
		tmp = tmp->next;
	}

	tmp = ls->dirs;
	while (tmp)
	{
		if (!tmp->close)
		{
			ft_printf("\n%s:\n", tmp->name);
			ft_printf("ls->total:[{green}  %u  {eoc}]\n", tmp->total);
			check_head(tmp->head);
		}
		else
			ft_printf("\n%s:\nls: %s: Permission denied\n", tmp->name, tmp->name);
		tmp = tmp->next;
	}

}
/*****************************************************
******************************************************/

int		main(int argc, char **argv)
{
	t_ls	*ls;
	int		i;

	i = 0;
	ls = (t_ls *)malloc(sizeof(t_ls));
	ft_bzero(ls, sizeof(t_ls));
	ls->files = (t_dir *)malloc(sizeof(t_dir));
	ft_bzero(ls->files, sizeof(t_dir));
	if (argc > 1 && argv[1][0] == '-' && ++i)
		check_flags(ls, argv[1]);
	if ((argc > 1 && !ls->flag) || (argc > 2 && ls->flag))
	{
		while (++i < argc)
			check_file_or_dir(ls, argv[i]);
	}
	else
		read_dir_info(ls, ".");

	ft_printf("======> SORT!!! <======\n");
	if (ls->files && ls->files->head)
		sort_lists(ls, ls->files);
	if (ls->dirs && ls->dirs->head)
		sort_lists(ls, ls->dirs);

	check_ls(ls);
//	output(ls);



	free_lists(ls->dirs);
	system("leaks a.out");
	return (0);
}
