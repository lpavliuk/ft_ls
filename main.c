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

#include "ls.h"

int		main(int argc, char **argv)
{
	t_ls *ls;

	ls = (t_ls *)malloc(sizeof(t_ls));
	ls->stat = (struct stat *)malloc(sizeof(struct stat));
	ls->dir = (struct dirent *)malloc(sizeof(struct dirent));
	if (argc > 1)
	{
		ls->fd_dir = opendir(argv[1]);
		while ((ls->dir = readdir(ls->fd_dir)))
		{
			ft_printf("=========================\n");
			ft_printf("[{green}  %s   {eoc}]\n", ls->dir->d_name);
			stat(ls->dir->d_name, ls->stat);
			ft_printf("id: %d\n", ls->stat->st_dev);
			ft_printf("inode: %d\n", ls->stat->st_ino);
			ft_printf("uid: %d\n", ls->stat->st_uid);
			ft_printf("mode: %lld\n", ls->stat->st_mode);
			ft_printf("size: %lld\n", ls->stat->st_size);
			ft_bzero(ls->stat, sizeof(*ls->stat));
		}
	}
	else
		ft_printf("OK!\n");
	return (0);
}