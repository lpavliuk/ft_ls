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

void	read_dir_info(t_ls *ls, const char *dir_name)
{
	t_dir	*dir;
	t_info  *file;
	char    *pwd;

	dir = new_dir(&ls->dirs, dir_name);

	ls->fd_dir = opendir(dir_name);
	while ((ls->file = readdir(ls->fd_dir)))
    {
		file = new_file(&dir->head);

		file->name_file = ft_strdup(ls->file->d_name);
		pwd = ft_strjoin_dir(dir_name, file->name_file);
		lstat(pwd, &ls->stat);
		free(pwd);

		file->nlinks = ls->stat.st_nlink;
		file->uid = ls->stat.st_uid;
		file->gid = ls->stat.st_gid;
		file->rdev = ls->stat.st_rdev;
		file->blocks = ls->stat.st_blocks;
		file->size = ls->stat.st_size;

		check_mode(ls->stat.st_mode, &file->mode[0]); // ONLY for flags -l and -n !!!

		file->atime = (size_t)ls->stat.st_atime;
		file->mtime = (size_t)ls->stat.st_mtime;
		file->ctime = (size_t)ls->stat.st_ctime;

		ft_strncpy(&file->data[0], ctime(&ls->stat.st_ctime), 24);

		dir->total += ls->stat.st_blocks;
		ft_bzero(&ls->stat, sizeof(ls->stat));
	}
	closedir(ls->fd_dir);
}

int		main(int argc, char **argv)
{
	t_ls *ls;
	t_dir	*tmp;

	ls = (t_ls *)malloc(sizeof(t_ls));
	ft_bzero(ls, sizeof(*ls));
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
