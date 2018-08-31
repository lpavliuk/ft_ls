/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 16:47:31 by opavliuk          #+#    #+#             */
/*   Updated: 2018/03/28 20:21:09 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	i;
	char	*d;

	i = 0;
	if (s == NULL || !(*f))
		return (NULL);
	i = ft_strlen(s);
	d = (char *)malloc(sizeof(char) * (i + 1));
	if (d == NULL)
		return (NULL);
	ft_bzero(d, (i + 1));
	i = 0;
	while (s[i] != '\0')
	{
		d[i] = f(s[i]);
		i++;
	}
	d[i] = '\0';
	return (d);
}
