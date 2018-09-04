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

#include <ls.h>

t_info	*new_file(t_info *head)
{
	if (!head)
	{
		head = (t_info *)malloc(sizeof(t_info));
		ft_bzero(head, sizeof(t_info));
		return (head);
	}
	else
	{
		while (head->next)
			head = head->next;
		head->next = (t_info *)malloc(sizeof(t_info));
		ft_bzero(head->next, sizeof(t_info));
		return (head->next);
	}
}

int		main(int argc, char **argv)
{
	t_ls *ls;
	t_info *file;
	char *pwd;
	char *tmp;

	ls = (t_ls *)malloc(sizeof(t_ls));
	ft_bzero(ls, sizeof(*ls));
	if (argc > 1)
	{
		ls->fd_dir = opendir(argv[1]);
		
		while ((ls->dir = readdir(ls->fd_dir)))
		{
			file = new_file(ls->head);
			file->name = ft_strdup(ls->dir->d_name);			

			ft_printf("=========================\n");
			ft_printf("file->name:[{green}  %s   {eoc}]\n", file->name);
			
			pwd = ft_strjoin(argv[1], "/");
			tmp = pwd;
			pwd = ft_strjoin(pwd, ls->dir->d_name);
			free(tmp);
			stat(pwd, &ls->stat);
			free(pwd);
			
			ft_printf("id: %d\n", ls->stat.st_dev);
			ft_printf("inode: %d\n", ls->stat.st_ino);
			ft_printf("uid: %d\n", ls->stat.st_uid);
			ft_printf("mode: %lld\n", ls->stat.st_mode);
			ft_printf("mode [octal]: %s\n", ft_itoa_base(ls->stat.st_mode, 8));

			check_mode(ls->stat.st_mode, &file->mode[0]);

			ft_printf("file->mode:[ {blue}  %s  {eoc}]\n", file->mode);
			
			file->size = ls->stat.st_size;
			
			ft_printf("file->size:[{red} %lld   {eoc}]\n", file->size);
			
			ft_printf("blocks: %lld\n", ls->stat.st_blocks);
			
			ft_printf("atime: %s", ctime(&ls->stat.st_atime));
			ft_printf("mtime: %s", ctime(&ls->stat.st_mtime));
			ft_printf("ctime: %s", ctime(&ls->stat.st_ctime));
			
			ft_strncpy(&file->time[0], ctime(&ls->stat.st_ctime), 24);

			ft_printf("file->time:[{yellow}  %s {eoc}]\n", file->time);

			ls->total += ls->stat.st_blocks;
			ft_bzero(&ls->stat, sizeof(ls->stat));
		
		}
		
		closedir(ls->fd_dir);
		
		ft_printf("=========================\n");
		ft_printf("ls->total:[{pink}  %u  {eoc}]\n", ls->total);
	}
	else
		ft_printf("OK!\n");
	// system("leaks a.out");
	return (0);
}
