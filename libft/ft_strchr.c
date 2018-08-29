/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 12:50:53 by opavliuk          #+#    #+#             */
/*   Updated: 2018/04/13 21:54:04 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	uintmax_t		mask;
	const uintmax_t *ptr;

	i = sizeof(uintmax_t);
	ptr = (const uintmax_t *)s;
	mask = c + 1;
	while (i--)
		mask = (mask << 8) + (c + 1);
	i = -1;
	while (1)
	{
		if (((*ptr - mask) & ~(*ptr) & 0x8080808080808080L)
			|| ((*ptr - 0x101010101010101L) & ~(*ptr) & 0x8080808080808080L))
		{
			s = (const char *)ptr;
			while (s[++i] != c && s[i] != '\0')
				;
			if (s[i] == c)
				return ((char *)s + i);
			else
				return (NULL);
		}
		ptr++;
	}
}
