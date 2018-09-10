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
/*****************************************************
******************************************************/

void	sort_lists(t_ls *ls)
{
	if (ls->flag & FLAG_T)
		sort_list_btime(ls->dirs, ls->dirs->head, ls->dirs->last_file->prev);
	else
		sort_list_bname(ls->dirs, ls->dirs->head, ls->dirs->last_file->prev);
}

int		main(int argc, char **argv)
{
	t_ls	*ls;
	t_dir	*tmp;
	int		i;

	i = 0;
	ls = (t_ls *)malloc(sizeof(t_ls));
	ft_bzero(ls, sizeof(t_ls));
	if (argc > 1 && argv[1][0] == '-' && ++i)
		check_flags(ls, argv[1]);
	if ((argc > 1 && !ls->flag) || (argc > 2 && ls->flag))
	{
		while (++i < argc)
			read_dir_info(ls, argv[i]);
	}
	else
		read_dir_info(ls, ".");

	tmp = ls->dirs;
	while (tmp)
	{
//		ft_printf("{blue}   %s: {eoc}\n", ls->dirs->name);
//		ft_printf("=========================\n");
//		ft_printf("ls->total:[{green}  %u  {eoc}]\n", ls->dirs->total);
		check_head(tmp->head);
		tmp = tmp->next;
	}
//
	ft_printf("======> SORT!!! <======\n");
	if (ls->dirs->head)
		sort_lists(ls);

	tmp = ls->dirs;
	while (tmp)
	{
//		ft_printf("{blue}   %s: {eoc}\n", tmp->name);
//		ft_printf("=========================\n");
		ft_printf("ls->total:[{green}  %u  {eoc}]\n", tmp->total);
		check_head(tmp->head);
		tmp = tmp->next;
	}

//	output(ls);



	free_lists(tmp);
//	system("leaks a.out");
	return (0);
}
