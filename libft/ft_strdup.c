/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 13:56:55 by opavliuk          #+#    #+#             */
/*   Updated: 2018/04/13 22:16:43 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char		*d;
	char		*begin;
	uintmax_t	*ptr_d;
	uintmax_t	*ptr_s;

	d = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (d == NULL)
		return (NULL);
	ptr_d = (uintmax_t *)d;
	ptr_s = (uintmax_t *)s1;
	begin = d;
	while (1)
	{
		if ((*ptr_s - 0x101010101010101L)
			& ~(*ptr_s) & 0x8080808080808080L)
		{
			d = (char *)ptr_d;
			s1 = (char *)ptr_s;
			while ((*d++ = *s1++))
				;
			return (begin);
		}
		*ptr_d++ = *ptr_s++;
	}
}
