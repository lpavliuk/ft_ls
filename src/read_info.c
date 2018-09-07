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
}

void				read_dir_info(t_ls *ls, const char *dir_name)
{
	t_dir	*dir;
	t_info	*file;

	dir = new_dir(&ls->dirs, dir_name);
	if (!(ls->fd_dir = opendir(dir_name)))
		return ;
	while ((ls->file = readdir(ls->fd_dir)))
	{
		file = new_file(&dir->head);
		file->name_file = ft_strdup(ls->file->d_name);
		file->pwd = ft_strjoin_dir(dir_name, file->name_file);
		read_file_info(ls, file); // ONLY for flags -l and -n !!!
		dir->total += ls->stat.st_blocks;
		ft_bzero(&ls->stat, sizeof(ls->stat));
	}
	closedir(ls->fd_dir);
}
