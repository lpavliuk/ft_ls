/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   staff.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 16:40:30 by opavliuk          #+#    #+#             */
/*   Updated: 2018/09/14 16:40:31 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ls.h"

void	ft_error(char *str)
{
	write(2, "ft_ls: ", 7);
	write(2, str, ft_strlen(str));
	write(2, ": Permission denied\n", 20);
}

void	check_dir(t_ls *ls, t_info *file)
{
	while (file)
	{
		if (file->mode[0] == 'd' && !(ls->flag & FLAG_D))
			read_dir_info(ls, file->name_file);
		file = file->next;
	}
}
