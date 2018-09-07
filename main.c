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
void	check_head(t_info *head)
{
	struct passwd	*pwuid;
	struct group	*group;

	while (head)
	{
		group = getgrgid(head->gid);
		pwuid = getpwuid(head->uid);
		ft_printf("===============================================\n");
        ft_printf("file->rdev:[{white}   %u   {eoc}]\n", head->rdev);
		ft_printf("file->blocks:[{pink}   %u   {eoc}]\n", head->blocks);
		ft_printf("file->name:[{green}  %s   {eoc}]\n", head->name_file);
		ft_printf("file->mode:[{blue}   %s  {eoc}]\n", head->mode);
		ft_printf("file->nlinks:[{white}   %u   {eoc}]\n", head->nlinks);
		ft_printf("file->uid:[{white}   %u   {eoc}]\n", head->uid);
		ft_printf("file->user:[{yellow}   %s   {eoc}]\n", pwuid->pw_name);
		ft_printf("file->gid:[{white}   %u   {eoc}]\n", head->gid);
		ft_printf("file->group:[{yellow}   %s   {eoc}]\n", group->gr_name);
		ft_printf("file->size:[{red} %u   {eoc}]\n", head->size);
		ft_printf("file->data:[{pink}  %s  {eoc}]\n", head->data);
		head = head->next;
	}
}
/*****************************************************
******************************************************/

void	ft_usage(const char flag)
{
	ft_printf("ls: illegal option -- %c\n", flag);
	ft_putendl("usage: ls [-laRrtnGd] [file ...]");
	exit(0);
}

void	check_flags(t_ls *ls, const char *flag)
{
	while (*flag++ != '\0')
	{
		if (*flag == 'l')
			ls->flag |= 1;
		else if (*flag == 'a')
			ls->flag |= 2;
		else if (*flag == 'R')
			ls->flag |= 4;
		else if (*flag == 'r')
			ls->flag |= 8;
		else if (*flag == 't')
			ls->flag |= 16;
		else if (*flag == 'n')
			ls->flag |= 32;
		else if (*flag == 'G')
			ls->flag |= 64;
		else if (*flag == 'd')
			ls->flag |= 128;
		else if (*flag != '\0')
			ft_usage(*flag);
	}
}

int		main(int argc, char **argv)
{
	t_ls *ls;
	t_dir	*tmp;

	ls = (t_ls *)malloc(sizeof(t_ls));
	ft_bzero(ls, sizeof(*ls));
	if (argc > 1 && argv[1][0] == '-' && argc--)
		check_flags(ls, argv[1]);
	if (argc > 1)
	{
		while (--argc > 0)
			read_dir_info(ls, argv[argc]);
	}
	else
		read_dir_info(ls, ".");
	tmp = ls->dirs;
	while (ls->dirs)
	{
		ft_printf("{blue}   %s: {eoc}\n", ls->dirs->name);
		ft_printf("=========================\n");
		ft_printf("ls->total:[{green}  %u  {eoc}]\n", ls->dirs->total);
		check_head(ls->dirs->head);
		ls->dirs = ls->dirs->next;
	}

	free_lists(tmp);
	system("leaks a.out");
	return (0);
}
