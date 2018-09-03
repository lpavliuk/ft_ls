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

			check_mode(ls, ls->stat.st_mode, &ls->mode[0]);

			ft_printf("[{blue}  %s  {eoc}]\n", ls->mode);
			ft_printf("[size:{red} %lld   {eoc}]\n", ls->stat.st_size);
			ft_printf("blocks: %lld\n", ls->stat.st_blocks);

			total += ls->stat.st_blocks;
			ft_bzero(&ls->stat, sizeof(ls->stat));
		
		}
		
		closedir(ls->fd_dir);
		
		ft_printf("=========================\n");
		ft_printf("[total:{pink}  %u  {eoc}]\n", total);
	}
	else
		ft_printf("OK!\n");
	// system("leaks a.out");
	return (0);
}
