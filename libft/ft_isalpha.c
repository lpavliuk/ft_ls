/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 18:52:43 by opavliuk          #+#    #+#             */
/*   Updated: 2018/03/31 14:04:02 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z')
			|| (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
