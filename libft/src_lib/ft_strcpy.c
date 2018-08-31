/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 14:55:24 by opavliuk          #+#    #+#             */
/*   Updated: 2018/03/28 19:47:04 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	char		*begin;
	uintmax_t	*src_ptr;
	uintmax_t	*dst_ptr;

	begin = dst;
	src_ptr = (uintmax_t *)src;
	dst_ptr = (uintmax_t *)dst;
	while (1)
	{
		if (((*src_ptr - 0x101010101010101L)
			& ~(*src_ptr) & 0x8080808080808080L))
		{
			src = (const char *)src_ptr;
			dst = (char *)dst_ptr;
			while ((*dst++ = *src++))
				;
			return (begin);
		}
		*dst_ptr++ = *src_ptr++;
	}
}
