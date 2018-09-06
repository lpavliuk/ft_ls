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

	ft_printf("%p\n", head);
	while (head)
	{
		group = getgrgid(head->gid);
		pwuid = getpwuid(head->uid);
		ft_printf("===============================================\n");
		ft_printf("file->blocks:[{pink}   %u   {eoc}]\n", head->blocks);
		ft_printf("file->name:[{green}  %s   {eoc}]\n", head->name);
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

//void	read_info(t_ls *ls)
//{
//
//}

int		main(int argc, char **argv)
{
	t_ls *ls;
	t_info *file;
	char *pwd;

	ls = (t_ls *)malloc(sizeof(t_ls));
	ft_bzero(ls, sizeof(*ls));
	if (argc > 1)
	{
		ls->fd_dir = opendir(argv[1]);
		
		while ((ls->dir = readdir(ls->fd_dir)))
		{
			ft_printf("====> %s <====\n", ls->dir->d_name);
			ft_printf("=========================\n");
			file = new_file(&ls->head);
			file->name = ft_strdup(ls->dir->d_name);			
			
			pwd = ft_strjoin_dir(argv[1], ls->dir->d_name);
			lstat(pwd, &ls->stat);
			free(pwd);
			ft_printf("rdev: %lld\n", ls->stat.st_rdev);			
			ft_printf("inode: %d\n", ls->stat.st_ino);
			ft_printf("links: %d\n", ls->stat.st_nlink);
			
			file->nlinks = ls->stat.st_nlink;
			file->uid = ls->stat.st_uid;
			file->gid = ls->stat.st_gid;
			file->rdev = ls->stat.st_rdev;

			ft_printf("major: %d\n", major(file->rdev));
			ft_printf("minor: %d\n", minor(file->rdev));
			ft_printf("mode: %lld\n", ls->stat.st_mode);
//			ft_printf("mode [octal]: %s\n", ft_itoa_base(ls->stat.st_mode, 8));
 
			ft_printf("size: %d\n", ls->stat.st_size);
						
			ft_printf("blocks: %d\n", ls->stat.st_blocks);

			file->blocks = ls->stat.st_blocks;
			
			check_mode(ls->stat.st_mode, &file->mode[0]);

			file->size = ls->stat.st_size;

			ft_printf("atime: %s", ctime(&ls->stat.st_atime));
			ft_printf("mtime: %s", ctime(&ls->stat.st_mtime));
			ft_printf("ctime: |%lld| - |%.24s|\n", ls->stat.st_ctime, ctime(&ls->stat.st_ctime));

			file->atime = (size_t)ls->stat.st_atime;
			file->mtime = (size_t)ls->stat.st_mtime;
			file->ctime = (size_t)ls->stat.st_ctime;
			
			ft_strncpy(&file->data[0], ctime(&ls->stat.st_ctime), 24);

			ls->total += ls->stat.st_blocks;
			ft_bzero(&ls->stat, sizeof(ls->stat));

		}
		closedir(ls->fd_dir);
//		check_head(ls->head);

		free_list(ls->head);
		
		ft_printf("=========================\n");
		ft_printf("ls->total:[{green}  %u  {eoc}]\n", ls->total);
	}
	else
		ft_printf("OK!\n");
	 system("leaks a.out");
	return (0);
}
