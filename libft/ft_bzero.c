/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 15:59:36 by opavliuk          #+#    #+#             */
/*   Updated: 2018/03/28 19:44:47 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	uintmax_t		*ptr;
	unsigned char	*dst;
	size_t			i;

	i = 0;
	ptr = (uintmax_t *)s;
	if (!n)
		return ;
	while (1)
	{
		if (n < sizeof(uintmax_t))
		{
			dst = (unsigned char *)ptr;
			while (n--)
				*dst++ = 0;
			return ;
		}
		n -= sizeof(uintmax_t);
		*ptr++ = 0;
	}
}
