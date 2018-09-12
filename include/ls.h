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
# include <sys/xattr.h>
# include <sys/acl.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include "../libft/include_lib/libft.h"

# define FLAG_L 0x01
# define FLAG_A 0x02
# define FLAG_R 0x04
# define FLAG_RR 0x08
# define FLAG_T 0x10
# define FLAG_N 0x20
# define FLAG_G 0x40
# define FLAG_D 0x80

typedef struct	s_info
{
	char			*name_file;
	char 			*pwd;
	char 			*name_group;
	char 			*name_user;
	char 			fail_file : 1;
	char			mode[12];
	char			data[25];
	nlink_t			nlinks;
	dev_t			rdev;	
	off_t			size;
	uid_t			uid;
	gid_t			gid;
	time_t			mtime;
	struct passwd	*pwuid;
	struct group	*group;
	struct s_info	*next;
	struct s_info	*prev;
}				t_info;

typedef struct	s_dir
{
	char 			*name;
	char 			close : 1;
	size_t			total;
	t_info			*head;
	t_info			*last_file;
	size_t 			s_name;
	size_t 			s_group;
	size_t			s_size;
	size_t			s_link;
	struct s_dir	*next;
	struct s_dir	*prev;
}				t_dir;

typedef struct	s_ls
{
	DIR				*fd_dir;
	struct dirent	*file;
	struct stat		stat;
	unsigned char 	flag;
	t_dir			*files;
	t_dir			*dirs;
	t_dir			*last_dir;
}				t_ls;

void			check_mode(t_info *file, unsigned int mode, char *permfile);
void			check_flags(t_ls *ls, char **argv, int *i);
char			*ft_strjoin_dir(char const *s1, char const *s2);
void			read_info(t_ls *ls, char *argv);
void			read_dir_info(t_ls *ls, const char *dir_name);
t_info			*new_file(t_dir *dir);
t_dir			*new_dir(t_ls *ls, const char *name);
void			sort_lists(t_ls *ls, t_dir *dir);
void			output_mode(t_ls *ls);
void			output_for(t_ls *ls, t_dir **next);
void 			output_ln(t_info *file, t_ls *ls, t_dir *dir);
void			output_just(t_dir *dir, char flag);

#endif
