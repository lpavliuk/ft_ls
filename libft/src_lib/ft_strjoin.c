/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 19:55:19 by opavliuk          #+#    #+#             */
/*   Updated: 2018/04/13 22:20:00 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*d;
	char		*begin;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	d = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	begin = d;
	if (d == NULL)
		return (NULL);
	ft_bzero(d, (ft_strlen(s1) + ft_strlen(s2) + 1));
	while (*s1 != '\0')
		*d++ = *s1++;
	while (*s2 != '\0')
		*d++ = *s2++;
	*d = '\0';
	return (begin);
}
