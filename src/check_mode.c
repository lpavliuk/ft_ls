/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 16:24:18 by opavliuk          #+#    #+#             */
/*   Updated: 2018/09/03 16:24:19 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ls.h"

static inline void	check_acl_and_xattr(t_info *file, char *permfile)
{
	acl_t		acl;
	acl_entry_t	buf;

	acl = acl_get_link_np(file->pwd, ACL_TYPE_EXTENDED);
	if (listxattr(file->pwd, NULL, 0, XATTR_NOFOLLOW) > 0)
		permfile[10] = '@';
	else if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &buf) != -1)
		permfile[10] = '+';
	else
		permfile[10] = ' ';
	acl_free(acl);
}

static inline void	check_type(const unsigned int *mode, char *permfile)
{
	if (S_ISDIR(*mode))
		permfile[0] = 'd';
	else if (S_ISBLK(*mode))
		permfile[0] = 'b';
	else if (S_ISCHR(*mode))
		permfile[0] = 'c';
	else if (S_ISLNK(*mode))
		permfile[0] = 'l';
	else if (S_ISFIFO(*mode))
		permfile[0] = 'p';
	else if (S_ISSOCK(*mode))
		permfile[0] = 's';
	else
		permfile[0] = '-';
}

static inline void	check_color(t_info *file)
{
	if (file->mode[0] == '-')
		ft_strncpy(&file->color[0], EOC, 5);
	else if (file->mode[0] == 'd')
		ft_strncpy(&file->color[0], BLUE, 5);
	else if (file->mode[0] == 'c')
		ft_strncpy(&file->color[0], YELLOW, 5);
	else if (file->mode[0] == 'l')
		ft_strncpy(&file->color[0], PINK, 5);
	else if (file->mode[0] == 'b')
		ft_strncpy(&file->color[0], CYAN, 5);
	else if (file->mode[0] == 'p')
		ft_strncpy(&file->color[0], WHITE, 5);
	else if (file->mode[0] == 's')
		ft_strncpy(&file->color[0], GREEN, 5);
}

void				check_mode(t_info *file, unsigned int mode, char *permfile)
{
	check_type((const unsigned int *)&mode, permfile);
	permfile[1] = (char)((mode & S_IRUSR) ? 'r' : '-');
	permfile[2] = (char)((mode & S_IWUSR) ? 'w' : '-');
	permfile[3] = (char)((mode & S_IXUSR) ? 'x' : '-');
	permfile[4] = (char)((mode & S_IRGRP) ? 'r' : '-');
	permfile[5] = (char)((mode & S_IWGRP) ? 'w' : '-');
	permfile[6] = (char)((mode & S_IXGRP) ? 'x' : '-');
	permfile[7] = (char)((mode & S_IROTH) ? 'r' : '-');
	permfile[8] = (char)((mode & S_IWOTH) ? 'w' : '-');
	permfile[9] = (char)((mode & S_IXOTH) ? 'x' : '-');
	if (mode & S_ISUID)
		permfile[3] = (char)((mode & S_IXUSR) ? 's' : 'S');
	if (mode & S_ISGID)
		permfile[6] = (char)((mode & S_IXGRP) ? 's' : 'l');
	if (mode & S_ISVTX)
		permfile[9] = (char)((mode & S_IXOTH) ? 't' : 'T');
	check_acl_and_xattr(file, permfile);
	check_color(file);
}
