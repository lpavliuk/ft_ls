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

void				check_flags(t_ls *ls, char **argv, int *i)
{
	while (argv[*i][0] == '-' && ++argv[*i])
	{
		while (*argv[*i] && *argv[*i] != '\0')
		{
			if (*argv[*i] == 'l')
				ls->flag |= 0x01;
			else if (*argv[*i] == 'a')
				ls->flag |= 0x02;
			else if (*argv[*i] == 'R')
				ls->flag |= 0x04;
			else if (*argv[*i] == 'r')
				ls->flag |= 0x08;
			else if (*argv[*i] == 't')
				ls->flag |= 0x10;
			else if (*argv[*i] == 'n')
				ls->flag |= 0x20;
			else if (*argv[*i] == 'G')
				ls->flag |= 0x40;
			else if (*argv[*i] == 'd')
				ls->flag |= 0x80;
			else
				ft_usage(*argv[*i]);
			++argv[*i];
		}
		++(*i);
	}
}
