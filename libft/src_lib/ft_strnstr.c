/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 13:50:36 by opavliuk          #+#    #+#             */
/*   Updated: 2018/03/28 20:17:21 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	check(char *b, char *l)
{
	while (*b++ == *l++)
	{
		if (*b == '\0' && *l == '\0')
			return (0);
	}
	if (*(l - 1) == '\0')
		return (0);
	else
		return (1);
}

char			*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	n;
	char	*b;
	char	*l;

	n = -1;
	b = (char *)big;
	l = (char *)little;
	if (*l == '\0')
		return (b);
	while (l[++n] != '\0')
		;
	while (*b != '\0' && len && n <= len)
	{
		l = (char *)little;
		if (*b++ == *l++)
		{
			if (!check((b - 1), (l - 1)))
				return (b - 1);
		}
		len--;
	}
	return (NULL);
}
