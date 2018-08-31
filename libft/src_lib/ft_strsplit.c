/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 10:41:23 by opavliuk          #+#    #+#             */
/*   Updated: 2018/03/28 20:24:16 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_letters(const char *g, char c)
{
	int l;

	l = 0;
	while (*g != '\0' && *g++ != c)
		l++;
	return (l);
}

static void		ft_wordscpy(char *d, const char *g, size_t l)
{
	while (l--)
		*d++ = *g++;
	*d = '\0';
}

static char		**ft_split(char **d, const char *g, char c)
{
	size_t k;
	size_t l;

	k = 0;
	l = 0;
	while (*g != '\0')
	{
		while (*g == c && *g++ != '\0')
			;
		if (*g == '\0')
			break ;
		l = count_letters(g, c);
		d[k] = (char *)malloc(sizeof(char) * (l + 1));
		if (d[k] == NULL)
		{
			ft_stralldel(d, k);
			return (NULL);
		}
		ft_bzero(d[k], (l + 1));
		ft_wordscpy(d[k], g, l);
		g += l;
		k++;
	}
	d[k] = 0;
	return (d);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**d;

	if (s == NULL)
		return (NULL);
	d = (char **)malloc(sizeof(char *) * (ft_count_words((char *)s, c) + 1));
	if (d == NULL)
		return (NULL);
	d = ft_split(d, s, c);
	return (d);
}
