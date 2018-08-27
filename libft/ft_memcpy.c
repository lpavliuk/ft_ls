/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:37:36 by opavliuk          #+#    #+#             */
/*   Updated: 2018/03/28 19:45:33 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	uintmax_t			*dst_ptr;
	const uintmax_t		*src_ptr;
	unsigned char		*d;
	const unsigned char	*s;

	src_ptr = (const uintmax_t *)src;
	dst_ptr = (uintmax_t *)dst;
	if (!n)
		return (dst);
	while (1)
	{
		if (n <= sizeof(uintmax_t))
		{
			s = (unsigned char *)src_ptr;
			d = (unsigned char *)dst_ptr;
			while ((*d++ = *s++) && --n > 0)
				;
			while (n-- > 1)
				*d++ = '\0';
			return (dst);
		}
		n -= sizeof(uintmax_t);
		*dst_ptr++ = *src_ptr++;
	}
}
