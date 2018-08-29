/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 16:47:46 by opavliuk          #+#    #+#             */
/*   Updated: 2018/03/28 20:17:47 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	int				i;
	const uintmax_t *ptr_s1;
	const uintmax_t *ptr_s2;

	i = -1;
	if (!(*s1) && !(*s2))
		return (0);
	ptr_s1 = (const uintmax_t *)s1;
	ptr_s2 = (const uintmax_t *)s2;
	while (1)
	{
		if (*ptr_s1 != *ptr_s2 || ((*ptr_s1 - 0x101010101010101L)
			& ~(*ptr_s1) & 0x8080808080808080L) ||
			((*ptr_s2 - 0x101010101010101L) & ~(*ptr_s2) & 0x8080808080808080L))
		{
			s1 = (const char *)ptr_s1;
			s2 = (const char *)ptr_s2;
			while (s1[++i] && s2[i] && s1[i] == s2[i])
				;
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		ptr_s1++ && ptr_s2++;
	}
}
