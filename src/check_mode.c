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

static inline void	check_type(unsigned int *mode, char *permfile)
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
		permfile[0] = 'c';
	else
		permfile[0] = '-';
}

void				check_mode(unsigned int mode, char *permfile)
{
	check_type(&mode, permfile);
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
}
