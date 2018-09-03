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

#include <ls.h>

static void	check_mode_dir(t_ls *ls, unsigned int *mode)
{
	if (*mode & S_IFREG)
		*mode ^= S_IFREG;
	else if (*mode & S_IFDIR)
	{
		ls->mode[0] = 'd';
		*mode ^= S_IFDIR;
	}
}

void		check_mode(t_ls *ls, unsigned int mode, char *permfile)
{
	int			n;
	char		*perm;

	n = 3;
	ft_strcpy(permfile, "---------");
	check_mode_dir(ls, &mode);
	while (--n >= 0)
	{
		if ((((mode & 7) == 7) && (perm = "rwx"))
		|| (((mode & 6) == 6) && (perm = "rw-"))
		|| (((mode & 5) == 5) && (perm = "r-x"))
		|| (((mode & 3) == 3) && (perm = "-wx"))
		|| ((mode & 4) && (perm = "r--"))
		|| ((mode & 2) && (perm = "-w-"))
		|| ((mode & 1) && (perm = "--x")))
			ft_memcpy(&permfile[1 + n * 3], perm, 3);
		mode >>= 3;
	}
	if (mode & 1)
		permfile[9] = (ls->mode[9] == 'x') ? 't' : 'T';
	if (mode & 2)
		permfile[6] = (ls->mode[6] == 'x') ? 's' : 'S';
	if (mode & 4)
		permfile[3] = (ls->mode[3] == 'x') ? 's' : 'S';
}
