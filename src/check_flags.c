/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 20:29:19 by opavliuk          #+#    #+#             */
/*   Updated: 2018/09/07 20:29:20 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ls.h"

static inline void	ft_usage(const char flag)
{
	ft_printf("ls: illegal option -- %c\n", flag);
	ft_putstr("usage: ls [-laRrtnGd] [file ...]\n");
	exit(0);
}

void				check_flags(t_ls *ls, const char *flag)
{
	(*(flag + 1)) ? ++flag : 0;
	while (flag && *flag != '\0')
	{
		if (*flag == 'l')
			ls->flag |= 0x01;
		else if (*flag == 'a')
			ls->flag |= 0x02;
		else if (*flag == 'R')
			ls->flag |= 0x04;
		else if (*flag == 'r')
			ls->flag |= 0x08;
		else if (*flag == 't')
			ls->flag |= 0x10;
		else if (*flag == 'n')
			ls->flag |= 0x20;
		else if (*flag == 'G')
			ls->flag |= 0x40;
		else if (*flag == 'd')
			ls->flag |= 0x80;
		else
			ft_usage(*flag);
		++flag;
	}
}
