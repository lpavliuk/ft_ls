/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <opavliuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 13:12:58 by opavliuk          #+#    #+#             */
/*   Updated: 2018/05/02 13:37:05 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	const uintmax_t	*ptr;
	const char		*str;
	int				i;

	i = -1;
	ptr = (const uintmax_t *)s;
	while (1)
	{
		if (((*ptr - 0x101010101010101L)
			& ~(*ptr) & 0x8080808080808080L))
		{
			str = (const char *)ptr;
			while (str[++i] != '\0')
				;
			return (str - s + i);
		}
		ptr++;
	}
}
