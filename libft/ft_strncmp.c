/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 17:24:22 by opavliuk          #+#    #+#             */
/*   Updated: 2018/03/28 20:18:09 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	const uintmax_t *ptr_s1;
	const uintmax_t *ptr_s2;

	i = 0;
	ptr_s1 = (const uintmax_t *)s1;
	ptr_s2 = (const uintmax_t *)s2;
	while (1)
	{
		if (n < sizeof(uintmax_t) || *ptr_s1 != *ptr_s2)
		{
			s1 = (const char *)ptr_s1;
			s2 = (const char *)ptr_s2;
			while (s1[i] == s2[i] && s1[i] && s2[i++] && n-- > 0)
				;
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		n -= sizeof(uintmax_t);
		ptr_s1++;
		ptr_s2++;
	}
}
