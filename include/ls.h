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
# include <time.h>

typedef struct	s_info
{
	char			*name;
	char			mode[11];
	size_t			size;
	char			time[25];
	struct s_info	*next;
}				t_info;

typedef struct	s_ls
{
	DIR				*fd_dir;
	struct dirent	*dir;
	struct stat		stat;
	size_t			total;
	t_info			*head;
}				t_ls;

void			check_mode(unsigned int mode, char *permfile);

#endif
