/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 19:11:45 by opavliuk          #+#    #+#             */
/*   Updated: 2018/08/31 19:11:48 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include "../libft/include_lib/libft.h"

typedef struct	s_info
{
	char			*name_file;
	char 			*pwd;
	char			mode[12];
	char			data[25];
	nlink_t			nlinks;
	dev_t			rdev;	
	off_t			size;
	uid_t			uid;
	gid_t			gid;
	blkcnt_t		blocks;
	size_t			atime;
	size_t			mtime;
	size_t			ctime;
	struct s_info	*next;
}				t_info;

typedef struct	s_dir
{
	char 			*name;
	size_t			total;
	t_info			*head;
	struct s_dir	*next;
}				t_dir;

typedef struct	s_ls
{
	DIR				*fd_dir;
	struct dirent	*file;
	struct stat		stat;
	t_dir			*dirs;
}				t_ls;

void			check_mode(unsigned int mode, char *permfile);
char			*ft_strjoin_dir(char const *s1, char const *s2);
void			read_dir_info(t_ls *ls, const char *dir_name);
t_info			*new_file(t_info **head);
t_dir			*new_dir(t_dir **dir, const char *name);
void			free_lists(t_dir *head);

#endif
