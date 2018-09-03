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

# include <libft.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>

typedef struct	s_ls
{
	DIR				*fd_dir;
	struct dirent	*dir;
	struct stat		stat;
	char			mode[11];
}				t_ls;

void		check_mode(t_ls *ls, unsigned int mode, char *permfile);

#endif
