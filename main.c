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

void	check_mode(t_ls *ls)
{
	int			n;
	int			mode;

	mode = ls->stat.st_mode;
	n = 3;
	while (--n >= 0)
	{
		if ((mode & 7) == 7)
			ft_memcpy(&ls->mode[1 + n * 3], "rwx", 3);
		else if ((mode & 6) == 6)
			ft_memcpy(&ls->mode[1 + n * 3], "rw-", 3);
		else if ((mode & 5) == 5)
			ft_memcpy(&ls->mode[1 + n * 3], "r-x", 3);
		else if ((mode & 3) == 3)
			ft_memcpy(&ls->mode[1 + n * 3], "-wx", 3);
		else if ((mode & 4) == 4)
			ft_memcpy(&ls->mode[1 + n * 3], "r--", 3);
		else if ((mode & 2) == 2)
			ft_memcpy(&ls->mode[1 + n * 3], "-w-", 3);
		else if ((mode & 1) == 1)
			ft_memcpy(&ls->mode[1 + n * 3], "--x", 3);
		else
			ft_memcpy(&ls->mode[1 + n * 3], "---", 3);
		mode >>= 3;
	}
}

int		main(int argc, char **argv)
{
	t_ls *ls;
	char *pwd;
	char *tmp;
	unsigned int total;

	ls = (t_ls *)malloc(sizeof(t_ls));
	ft_bzero(ls, sizeof(*ls));
	total = 0;
	if (argc > 1)
	{
		ls->fd_dir = opendir(argv[1]);
		while ((ls->dir = readdir(ls->fd_dir)))
		{
			ft_printf("=========================\n");
			ft_printf("[{green}  %s   {eoc}]\n", ls->dir->d_name);
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

			if (ls->stat.st_mode & S_IFREG) // Is this a file?
			{	
				ft_printf("REG!\n");
				ls->mode[0] = '-';
				ls->stat.st_mode ^= S_IFREG;
				ft_printf("%o\n", ls->stat.st_mode);
			}
			else if (ls->stat.st_mode & S_IFDIR) // Is this a directory?
			{
				ft_printf("DIR!\n");
				ls->mode[0] = 'd';
				ls->stat.st_mode ^= S_IFDIR;
				ft_printf("%o\n", ls->stat.st_mode);
			}

			check_mode(ls);

			int i = -1;
			while (++i < 10)
				ft_printf("%c", ls->mode[i]);
			ft_printf("\n");

			ft_printf("size: %lld\n", ls->stat.st_size);
			ft_printf("blocks: %lld\n", ls->stat.st_blocks);
			total += ls->stat.st_blocks;
			ft_bzero(&ls->stat, sizeof(ls->stat));
		}
		closedir(ls->fd_dir);
		ft_printf("=========================\n");
		ft_printf("total: %u\n", total);
	}
	else
		ft_printf("OK!\n");
	// system("leaks a.out");
	return (0);
}
