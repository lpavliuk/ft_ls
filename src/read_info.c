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

#include <ls.h>

static inline void	check_time(t_info *file)
{
	time_t	current;
	char	*str;

	current = time(NULL);
	ft_strncpy(&file->data[0], ctime(&file->mtime), 24);
	if (current - file->mtime > 15778463 || current < file->mtime)
	{
		str = ft_strdup(file->data);
		ft_bzero(file->data, 25);
		ft_strncpy(&file->data[0], str, 10);
		file->data[10] = ' ';
		ft_strncpy(&file->data[11], &str[19], 5);
		free(str);
	}
}

static inline void	find_link(t_info *file)
{
	char	*tmp;
	char	*buf;
	ssize_t	size;

	buf = malloc(PATH_MAX);
	ft_bzero(buf, PATH_MAX);
	if (file->pwd)
		size = readlink(file->pwd, buf, PATH_MAX);
	else
		size = readlink(file->name_file, buf, PATH_MAX);
	buf[size] = '\0';
	tmp = file->name_file;
	file->name_file = ft_strjoin(file->name_file, " -> ");
	free(tmp);
	tmp = file->name_file;
	file->name_file = ft_strjoin(file->name_file, buf);
	free(tmp);
	free(buf);
}

static inline void	read_file_info(t_ls *ls, t_dir *dir, t_info *file)
{
	size_t n;

	lstat(file->pwd, &ls->stat);
	file->nlinks = ls->stat.st_nlink;
	file->uid = ls->stat.st_uid;
	file->gid = ls->stat.st_gid;
	file->group = getgrgid(file->gid);
	file->pwuid = getpwuid(file->uid);
	(file->group) ? file->name_group = ft_strdup(file->group->gr_name) : 0;
	(file->pwuid) ? file->name_user = ft_strdup(file->pwuid->pw_name) : 0;
	file->rdev = ls->stat.st_rdev;
	file->size = ls->stat.st_size;
	file->mtime = (size_t)ls->stat.st_mtime;
	check_mode(file, ls->stat.st_mode, &file->mode[0]);
	(file->mode[0] == 'l') ? find_link(file) : 0;
	(file->mode[0] == 'c') ? dir->s_size = 8 : 0;
	n = (file->group) ? ft_strlen(file->group->gr_name) + 1 : 0;
	(n > dir->s_group) ? dir->s_group = n : 0;
	n = (file->pwuid) ? ft_strlen(file->pwuid->pw_name) + 1 : 0;
	(n > dir->s_name) ? dir->s_name = n : 0;
	n = ft_count(file->size, 10);
	(n > dir->s_size) ? dir->s_size = n : 0;
	n = ft_count(file->nlinks, 10);
	(n > dir->s_link) ? dir->s_link = n : 0;
	check_time(file);
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
			continue;
		file = new_file(dir);
		file->name_file = ft_strdup(ls->file->d_name);
		file->pwd = ft_strjoin_dir(dir_name, file->name_file);
		if (ls->flag & FLAG_L || ls->flag & FLAG_N
		|| ls->flag & FLAG_T || ls->flag & FLAG_G || ls->flag & FLAG_R)
			read_file_info(ls, dir, file);
		dir->total += ls->stat.st_blocks;
		ft_bzero(&ls->stat, sizeof(ls->stat));
	}
	closedir(ls->fd_dir);
}

void				read_info(t_ls *ls, char *argv)
{
	t_info	*file;
	int		num;

	num = lstat(argv, &ls->stat);
	file = new_file(ls->files);
	file->name_file = ft_strdup(argv);
	if (num < 0)
		file->fail_file = 1;
	else
		read_file_info(ls, ls->files, file);
	ft_bzero(&ls->stat, sizeof(ls->stat));
}
