/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_dir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 12:32:12 by opavliuk          #+#    #+#             */
/*   Updated: 2018/09/06 12:32:13 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ls.h"

char	*ft_strjoin_dir(char const *s1, char const *s2)
{
	char	*d;
	char	*begin;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	d = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	begin = d;
	if (d == NULL)
		return (NULL);
	ft_bzero(d, (ft_strlen(s1) + ft_strlen(s2) + 2));
	while (*s1 != '\0')
		*d++ = *s1++;
	if (*(s1 - 1) != '/')
		*d++ = '/';
	while (*s2 != '\0')
		*d++ = *s2++;
	*d = '\0';
	return (begin);
}
