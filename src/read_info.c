/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 11:32:20 by opavliuk          #+#    #+#             */
/*   Updated: 2018/09/07 11:32:21 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ls.h"

static inline void	find_link(t_info *file)
{
	char	*tmp;
	char	*buf;
	ssize_t	size;

	buf = malloc(PATH_MAX);
	ft_bzero(buf, PATH_MAX);
	size = readlink(file->pwd, buf, PATH_MAX);
	buf[size] = '\0';
	ft_printf("size: %zu | %s ---> %.*s\n", size, file->pwd, (int)size, buf);
	tmp = file->name_file;
	file->name_file = ft_strjoin(file->name_file, " -> ");
	free(tmp);
	tmp = file->name_file;
	file->name_file = ft_strjoin(file->name_file, buf);
	free(tmp);
	free(buf);
}

static inline void	read_file_info(t_ls *ls, t_info *file)
{
	lstat(file->pwd, &ls->stat);
	file->nlinks = ls->stat.st_nlink;
	file->uid = ls->stat.st_uid;
	file->gid = ls->stat.st_gid;
	file->rdev = ls->stat.st_rdev;
	file->blocks = ls->stat.st_blocks;
	file->size = ls->stat.st_size;
	file->atime = (size_t)ls->stat.st_atime;
	file->mtime = (size_t)ls->stat.st_mtime;
	file->ctime = (size_t)ls->stat.st_ctime;
	ft_strncpy(&file->data[0], ctime(&ls->stat.st_ctime), 24);
	check_mode(file, ls->stat.st_mode, &file->mode[0]);
	if (file->mode[0] == 'l')
		find_link(file);
}

void				read_dir_info(t_ls *ls, const char *dir_name)
{
	t_dir	*dir;
	t_info	*file;

	dir = new_dir(ls, dir_name);
	if ((ls->fd_dir = opendir(dir_name)) <= 0)
	{
		dir->close = 1;
		return ;
	}
	while ((ls->file = readdir(ls->fd_dir)))
	{
		if (!(ls->flag & FLAG_A) && ls->file->d_name[0] == '.')
			continue ;
		file = new_file(dir);
		file->name_file = ft_strdup(ls->file->d_name);
		file->pwd = ft_strjoin_dir(dir_name, file->name_file);
		if (ls->flag & FLAG_L || ls->flag & FLAG_N || ls->flag & FLAG_T)
			read_file_info(ls, file);
		dir->total += ls->stat.st_blocks;
		ft_bzero(&ls->stat, sizeof(ls->stat));
	}
	closedir(ls->fd_dir);
}

void				check_file_or_dir(t_ls *ls, char *argv)
{
	t_info	*file;
	int 	num;

	num = lstat(argv, &ls->stat);
	if (S_ISDIR(ls->stat.st_mode))
		read_dir_info(ls, argv);
	else
	{
		file = new_file(ls->files);
		file->name_file = ft_strdup(argv);
		if (num < 0)
			file->fail_file = 1;
		else
			read_file_info(ls, file);
		ft_bzero(&ls->stat, sizeof(ls->stat));
	}
}
